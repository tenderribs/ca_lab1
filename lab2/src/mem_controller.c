#include "mem_controller.h"
#include "cache.h"
#include "stdio.h"
#include <assert.h>

void init_memory_controller(MemController *mc, uint32_t queue_capacity) {
    mc->queue = (MemRequest *)calloc(queue_capacity, sizeof(MemRequest));
    mc->queue_capacity = queue_capacity;
    mc->queue_size = 0;
    mc->cmd_bus_free_cycle = 0;
    mc->data_bus_free_cycle = 0;

    // Initialize all banks
    mc->banks = (Bank *)calloc(NUM_BANKS, sizeof(Bank));
}

void free_memory_controller(MemController *mc) { free(mc->queue); }

static uint32_t get_bank_index(uint32_t address) {
    return (address >> 5) & 0x7; // bits [7:5]
}

static uint32_t get_row_index(uint32_t address) {
    return address >> 13; // bits [31:13]
}

static RowBufferStatus get_row_buffer_status(Bank *bank, uint32_t row) {
    if (!bank->has_open_row) {
        return ROW_BUFFER_MISS;
    }

    // row buffer has open row
    if (bank->open_row == row) {
        return ROW_BUFFER_HIT;
    }
    return ROW_BUFFER_CONFLICT;
}

// Check if a request can be scheduled in the current cycle
static int is_request_schedulable(MemController *mc, MemRequest *req, uint32_t curr_cycle) {
    assert(req->valid); // sanity check

    uint32_t bank = get_bank_index(req->address);
    uint32_t row = get_row_index(req->address);

    RowBufferStatus rb_status = get_row_buffer_status(&mc->banks[bank], row);

    // Determine timing sequence
    uint8_t num_commands = 0;
    switch (rb_status) {
    case ROW_BUFFER_HIT:
        num_commands = 1; // READ/WRITE
        break;
    case ROW_BUFFER_MISS:
        num_commands = 2; // ACTIVATE + READ/WRITE
        break;
    case ROW_BUFFER_CONFLICT:
        num_commands = 3; // PRECHARGE + ACTIVATE + READ/WRITE
        break;
    }
    assert(num_commands && num_commands <= 3);

    // timing constraint example
    //         ┌────┐            ┌────┐
    // cmd-bus │CMD1│            │CMD2│
    //         ├────┴────────────┼────┴────────────┐
    // bank    │BANK_BUSY_CYCLES │BANK_BUSY_CYCLES │
    //         └─────────────────┴─────────────────┼──────────────┐
    // data-bus                                    │DATA_TF_CYCLES│
    //                   ─────────────────► t      └──────────────┘

    // ======================
    // 1. is CMD bus available for our commands?

    for (uint8_t our_cmd_nr = 0; our_cmd_nr < num_commands; our_cmd_nr++) {
        // calculate start and end cycle for all the cmds we execute
        uint32_t our_cmd_start = curr_cycle + our_cmd_nr * BANK_BUSY_CYCLES; // ~ 0, 100, 200
        uint32_t our_cmd_end = our_cmd_start + CMD_CYCLES - 1;               // ~ 3, 103, 203

        // check if any bank is scheduled to use the COMMAND bus
        for (size_t b = 0; b < NUM_BANKS; b++) {

            // skip timining constraint check if bank hasn't been used yet
            // has_open_row=1 can be used as a proxy for this situation because rows are never
            // closed due to row refreshes.
            if (!mc->banks[b].has_open_row)
                continue;

            // check for overlaps with each other bank's scheduled commands' start and end
            for (uint8_t sched_cmd = 0; sched_cmd < mc->banks[b].num_commands; sched_cmd++) {
                uint32_t sched_cmd_start = mc->banks[b].req_start + sched_cmd * BANK_BUSY_CYCLES;
                uint32_t sched_cmd_end = sched_cmd_start + CMD_CYCLES - 1;

                // reject if our access overlaps with an already scheduled request's
                // commands
                if (!(our_cmd_end < sched_cmd_start || our_cmd_start > sched_cmd_end))
                    return 0;
            }
        }
    }

    // ======================
    // 2. is data bus free?

    // Data transfer 100 - 149
    uint32_t data_tf_start = curr_cycle + num_commands * BANK_BUSY_CYCLES; // ~ 100, 200, 300
    uint32_t data_tf_end = data_tf_start + DATA_TF_CYCLES - 1;             // ~ 149, 249, 349

    // check if any other bank is scheduled to use the DATA bus
    for (size_t b = 0; b < NUM_BANKS; b++) {

        // skip timining constraint check if bank hasn't been used yet
        if (!mc->banks[b].has_open_row)
            continue;

        // shared data bus will be used when banks are done processing commands:
        uint32_t sched_tf_start =
            mc->banks[b].req_start + mc->banks[b].num_commands * BANK_BUSY_CYCLES;
        uint32_t sched_tf_end = sched_tf_start + DATA_TF_CYCLES - 1;

        // reject if the scheduled transfers would overlap with ours
        //      |sched_start      sched_end|
        // end  |                          | start
        if (!(data_tf_end < sched_tf_start || data_tf_start > sched_tf_end))
            return 0;
    }

    // ======================
    // 3. is the bank free?
    uint32_t req_end = curr_cycle + num_commands * BANK_BUSY_CYCLES - 1;

    // ensure no overlap between bank scheduled start and end
    uint32_t sched_start = mc->banks[bank].req_start;
    uint32_t sched_end = sched_start + mc->banks[bank].num_commands * BANK_BUSY_CYCLES - 1;

    // check for overlap
    if (mc->banks[bank].open_row && !(req_end < sched_start || curr_cycle > sched_end))
        return 0;

    return 1;
}

// Select best request to schedule using FR-FCFS policy
static MemRequest *select_request_to_schedule(MemController *mc, uint32_t current_cycle) {
    MemRequest *best = NULL;

    // check all the requests in the queue
    for (uint32_t i = 0; i < mc->queue_capacity; i++) {
        // only consider requests that have arrived in DRAM
        if (!mc->queue[i].valid || current_cycle < mc->queue[i].arrival_cycle)
            continue;

        if (!is_request_schedulable(mc, &mc->queue[i], current_cycle))
            continue;

        if (best == NULL) {
            best = &mc->queue[i];
            continue;
        }

        uint32_t best_bank = get_bank_index(best->address);
        uint32_t best_row = get_row_index(best->address);
        uint32_t curr_bank = get_bank_index(mc->queue[i].address);
        uint32_t curr_row = get_row_index(mc->queue[i].address);

        int best_is_hit =
            (mc->banks[best_bank].has_open_row && mc->banks[best_bank].open_row == best_row);
        int curr_is_hit =
            (mc->banks[curr_bank].has_open_row && mc->banks[curr_bank].open_row == curr_row);

        // Priority 1: Row buffer hits over misses
        if (curr_is_hit && !best_is_hit) {
            best = &mc->queue[i];
        } else if (best_is_hit && !curr_is_hit) {
            continue;
        }
        // Priority 2: Earlier arrival time
        else if (mc->queue[i].arrival_cycle < best->arrival_cycle) {
            best = &mc->queue[i];
        } else if (mc->queue[i].arrival_cycle == best->arrival_cycle) {
            // Priority 3: From MEM stage over fetch
            if (mc->queue[i].from_mem_stage && !best->from_mem_stage) {
                best = &mc->queue[i];
            }
        }
    }

    return best;
}

// Schedule and issue DRAM commands for a request
static void issue_dram_request(MemController *mc, MemRequest *req, uint32_t current_cycle) {
    uint32_t bank_idx = get_bank_index(req->address);
    uint32_t row = get_row_index(req->address);
    Bank *bank = &mc->banks[bank_idx];

    RowBufferStatus rb_status = get_row_buffer_status(bank, row);

    switch (rb_status) {
    case ROW_BUFFER_HIT:
        bank->num_commands = 1;
        break;
    case ROW_BUFFER_MISS:
        bank->num_commands = 2;
        break;
    case ROW_BUFFER_CONFLICT:
        bank->num_commands = 3;
        break;
    }

    assert(bank->num_commands >= 1 && bank->num_commands <= 3);

    // Update bus and bank states
    bank->req_start = current_cycle;
    bank->has_open_row = 1;
    bank->open_row = row;

    // Calculate when fill will be complete
    // Data arrives at L2 after data transfer + latency back to L2
    uint32_t fill_complete_cycle = current_cycle + bank->num_commands * BANK_BUSY_CYCLES +
                                   DATA_TF_CYCLES + MEM_TO_L2_LATENCY + L2_TO_MEM_LATENCY;

    // Update MSHR
    req->mshr->fill_ready_cycle = fill_complete_cycle;
}

void memory_controller_cycle(MemController *mc, uint32_t current_cycle) {
    // First, check for L2 hits that are ready this cycle
    for (size_t i = 0; i < NUM_MSHR; i++) {
        if (mshrs[i].valid && !mshrs[i].done) {
            if (mshrs[i].fill_ready_cycle > 0 && current_cycle >= mshrs[i].fill_ready_cycle) {
                printf("Marking fill as done\r\n");
                // Fill is ready - mark MSHR as done
                mshrs[i].done = 1;
            }
        }
    }

    // Add new L2 misses to memory request queue
    for (size_t i = 0; i < NUM_MSHR; i++) {
        if (mshrs[i].valid && !mshrs[i].done && mshrs[i].fill_ready_cycle == 0) {
            // Found unqueued L2 miss -> queue it
            printf("found L2 miss\r\n");

            // Find free queue slot
            int queued = 0;
            for (uint32_t j = 0; j < mc->queue_capacity; j++) {
                if (!mc->queue[j].valid) {
                    mc->queue[j].address = mshrs[i].address;
                    mc->queue[j].arrival_cycle = current_cycle;
                    mc->queue[j].from_mem_stage = (mshrs[i].is_icache == 1) ? 0 : 1;
                    mc->queue[j].mshr = &mshrs[i];
                    mc->queue[j].valid = 1;
                    mc->queue_size++;
                    queued = 1;

                    // Mark MSHR with impossible nonzero value so we don't queue it again
                    mshrs[i].fill_ready_cycle = 1;
                    break;
                }
            }

            if (!queued) {
                // should never happen with infinite queue
                printf("Couldn't add L2 miss to mem queue\r\n");
                assert(0);
            }
        }
    }

    // Try to schedule a request
    MemRequest *to_schedule = select_request_to_schedule(mc, current_cycle);

    if (to_schedule != NULL) {
        // Issue the request
        issue_dram_request(mc, to_schedule, current_cycle);

        // Remove from queue
        to_schedule->valid = 0;
        mc->queue_size--;
    }

    // Process completed fills
    for (uint32_t i = 0; i < mc->queue_capacity; i++) {
        if (mc->queue[i].valid && mc->queue[i].mshr->done) {
            // Fill is complete - insert into L2 cache
            insert_l2_block(mc->queue[i].address);
        }
    }
}