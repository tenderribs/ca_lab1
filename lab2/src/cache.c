#include "cache.h"
#include "shell.h"
#include "stdio.h"
#include <assert.h>
#include <stdlib.h>

// DRAM timing constants (in cycles)
#define DRAM_COMMAND_CYCLES 4
#define DRAM_BANK_BUSY_CYCLES 100
#define DRAM_DATA_TRANSFER_CYCLES 50
#define L2_HIT_LATENCY 15
#define L2_TO_MEM_LATENCY 5
#define MEM_TO_L2_LATENCY 5

void alloc_cache(Cache *c, uint32_t capacity, uint8_t num_ways,
                 uint8_t block_size) {
    c->block_size = block_size;
    c->num_sets = capacity / (block_size * num_ways);
    c->num_ways = num_ways;

    // compute block_bits = log2 of block_size
    uint32_t temp = block_size;
    c->block_bits = 0;
    while (temp > 1) {
        temp >>= 1;
        c->block_bits++;
    }

    // compute set_bits = log2 of num_sets
    temp = c->num_sets;
    c->set_bits = 0;
    while (temp > 1) {
        temp >>= 1;
        c->set_bits++;
    }

    // dynamically allocate memory for cache
    c->sets = malloc(sizeof(Set) * c->num_sets);
    for (size_t s = 0; s < c->num_sets; s++) {
        c->sets[s].blocks = malloc(sizeof(Block) * c->num_ways);

        for (size_t b = 0; b < c->num_ways; b++) {
            Block *block = &c->sets[s].blocks[b];

            block->tag = 0;
            block->valid = 0;
            block->recency = 0;
        }
    }
}

void free_cache(Cache *c) {
    // free the blocks in each set
    for (size_t s = 0; s < c->num_sets; s++) {
        // free the blocks
        free(c->sets[s].blocks);
    }

    // free the sets
    free(c->sets);
}

void update_lru(Cache *c, size_t set, size_t block) {
    uint32_t prev_recency = c->sets[set].blocks[block].recency;

    // increment the recency for valid blocks that were prev. more recent
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].valid &&
            c->sets[set].blocks[b].recency < prev_recency) {
            c->sets[set].blocks[b].recency++;
        }
    }

    // and most recently updated block gets the lru pos 0;
    c->sets[set].blocks[block].recency = 0;
}

static MSHR *find_mshr_for_address(uint32_t address) {
    // Align address to block boundary
    uint32_t block_addr = address & ~(BLOCK_SIZE - 1);

    for (size_t i = 0; i < NUM_MSHR; i++) {
        if (mshrs[i].valid &&
            (mshrs[i].address & ~(BLOCK_SIZE - 1)) == block_addr) {
            return &mshrs[i];
        }
    }
    return NULL;
}

static MSHR *allocate_mshr(uint32_t address, uint8_t is_icache) {
    for (size_t i = 0; i < NUM_MSHR; i++) {
        if (!mshrs[i].valid) {
            mshrs[i].address = address & ~(BLOCK_SIZE - 1);
            mshrs[i].valid = 1;
            mshrs[i].done = 0;
            mshrs[i].fill_ready_cycle = 0;
            mshrs[i].is_icache = is_icache;
            return &mshrs[i];
        }
    }
    return NULL;
}

static void free_mshr(MSHR *mshr) {
    mshr->valid = 0;
    mshr->done = 0;
    mshr->fill_ready_cycle = 0;
}

CacheAccessResult l1_cache_access(Cache *c, uint32_t address,
                                  uint8_t is_icache) {
    assert((address % 4 == 0) && "Address should be multiple of 4 bytes");

    // calculate the L1 set index and the tag
    uint32_t tag = (address >> (c->block_bits + c->set_bits));
    uint32_t set = ((address >> c->block_bits) & ((1 << c->set_bits) - 1));

    // check L1 set for any hits in set
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].tag == tag && c->sets[set].blocks[b].valid) {
            // HIT since tag matches and block is valid
            // -> update LRU positions of set's blocks
            update_lru(c, set, b);
            return CACHE_HIT;
        }
    }

    // MISS -> check if request already pending
    MSHR *existing_mshr = find_mshr_for_address(address);
    if (existing_mshr) {
        // Already have a pending request for this block
        return CACHE_MISS_WAIT;
    }

    // MISS -> probe L2 cache in same cycle
    return l2_cache_access(address, is_icache);
}

int check_l1_fill_ready(Cache *c, uint32_t address) {
    MSHR *mshr = find_mshr_for_address(address);
    if (mshr && mshr->done) {
        return 1;
    }
    return 0;
}

void complete_l1_fill(Cache *c, uint32_t address) {
    uint32_t tag = (address >> (c->block_bits + c->set_bits));
    uint32_t set = ((address >> c->block_bits) & ((1 << c->set_bits) - 1));

    // Find victim block using LRU
    size_t victim = 0;
    int found = 0;

    // 1. Look for invalid blocks first
    for (size_t b = 0; b < c->num_ways; b++) {
        if (!c->sets[set].blocks[b].valid) {
            victim = b;
            found = 1;
            break;
        }
    }

    // 2. If all blocks valid, use LRU
    if (!found) {
        for (size_t b = 0; b < c->num_ways; b++) {
            // find the least recently used block, set as victim
            if (c->sets[set].blocks[b].recency == (c->num_ways - 1)) {
                victim = b;
                break;
            }
        }
    }

    // Insert the block at victims place
    c->sets[set].blocks[victim].tag = tag;
    c->sets[set].blocks[victim].valid = 1;
    update_lru(c, set, victim);

    // Free the MSHR (done by caller or memory controller)
}

CacheAccessResult l2_cache_access(uint32_t address, uint8_t is_icache) {
    // L2 cache can only be probed if there are free MSHRs
    MSHR *mshr = allocate_mshr(address, is_icache);
    if (mshr == NULL) {
        return CACHE_NO_MSHR;
    }

    // calculate the L2 set index and the tag
    uint32_t tag = (address >> (l2cache.block_bits + l2cache.set_bits));
    uint32_t set =
        ((address >> l2cache.block_bits) & ((1 << l2cache.set_bits) - 1));

    // check L2 set for any hits in set
    for (size_t b = 0; b < l2cache.num_ways; b++) {
        if (l2cache.sets[set].blocks[b].tag == tag &&
            l2cache.sets[set].blocks[b].valid) {
            // L2 HIT - will send fill notification after 15 cycles
            update_lru(&l2cache, set, b);

            // Mark when fill will be ready (current cycle is in shell.c
            // stat_cycles)
            extern uint32_t stat_cycles;
            mshr->fill_ready_cycle = stat_cycles + L2_HIT_LATENCY;

            return CACHE_MISS_WAIT; // Not truly a miss, but L1 still waits for
                                    // fill
        }
    }

    // L2 MISS - need to go to memory
    // Add request to memory controller queue (will be done in
    // memory_controller_cycle) The memory controller will set mshr->done when
    // data is ready
    return CACHE_MISS_WAIT;
}

// Insert block into L2 cache when fill completes from memory
static void insert_l2_block(uint32_t address) {
    uint32_t tag = (address >> (l2cache.block_bits + l2cache.set_bits));
    uint32_t set =
        ((address >> l2cache.block_bits) & ((1 << l2cache.set_bits) - 1));

    // Find victim using LRU
    size_t victim = 0;
    int found = 0;

    // Look for invalid blocks first
    for (size_t b = 0; b < l2cache.num_ways; b++) {
        if (!l2cache.sets[set].blocks[b].valid) {
            victim = b;
            found = 1;
            break;
        }
    }

    // If all blocks valid, use LRU
    if (!found) {
        for (size_t b = 0; b < l2cache.num_ways; b++) {
            // evict least recently used block
            if (l2cache.sets[set].blocks[b].recency == (l2cache.num_ways - 1)) {
                victim = b;
                break;
            }
        }
    }

    // replace the victim
    l2cache.sets[set].blocks[victim].tag = tag;
    l2cache.sets[set].blocks[victim].valid = 1;
    l2cache.sets[set].blocks[victim].recency = 0;

    // Increment recency of all other valid blocks
    for (size_t b = 0; b < l2cache.num_ways; b++) {
        if (b != victim && l2cache.sets[set].blocks[b].valid) {
            l2cache.sets[set].blocks[b].recency++;
        }
    }
}

// ============================================================================
// Memory Controller Implementation
// ============================================================================

void init_memory_controller(MemController *mc, uint32_t queue_capacity) {
    mc->queue = malloc(sizeof(MemRequest) * queue_capacity);
    mc->queue_capacity = queue_capacity;
    mc->queue_size = 0;
    mc->cmd_bus_free_cycle = 0;
    mc->data_bus_free_cycle = 0;

    // Initialize all banks
    for (int i = 0; i < NUM_BANKS; i++) {
        mc->banks[i].busy = 0;
        mc->banks[i].ready_cycle = 0;
        mc->banks[i].has_open_row = 0;
        mc->banks[i].open_row = 0;
    }

    // Initialize queue entries
    for (uint32_t i = 0; i < queue_capacity; i++) {
        mc->queue[i].valid = 0;
    }
}

void free_memory_controller(MemController *mc) { free(mc->queue); }

static uint32_t get_bank_index(uint32_t address) {
    return (address >> 5) & 0x7; // bits [7:5]
}

static uint32_t get_row_index(uint32_t address) {
    return address >> 13; // bits [31:13]
}

typedef enum {
    ROW_BUFFER_HIT,
    ROW_BUFFER_MISS,
    ROW_BUFFER_CONFLICT
} RowBufferStatus;

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
static int is_request_schedulable(MemController *mc, MemRequest *req,
                                  uint32_t current_cycle) {
    if (!req->valid) // sanity check
        return 0;

    uint32_t bank = get_bank_index(req->address);
    uint32_t row = get_row_index(req->address);

    RowBufferStatus rb_status = get_row_buffer_status(&mc->banks[bank], row);

    // Determine command sequence and timing
    uint32_t first_cmd_cycle = current_cycle;
    uint32_t last_cmd_cycle = 0;
    uint32_t bank_free_cycle = 0;
    uint32_t data_cycle_start = 0;

    switch (rb_status) {
    case ROW_BUFFER_HIT:
        // Only READ/WRITE command needed
        last_cmd_cycle = first_cmd_cycle + DRAM_COMMAND_CYCLES - 1;
        bank_free_cycle = last_cmd_cycle + 1 + DRAM_BANK_BUSY_CYCLES;
        data_cycle_start = last_cmd_cycle + 1 + DRAM_BANK_BUSY_CYCLES;
        break;

    case ROW_BUFFER_MISS:
        // ACTIVATE, then READ/WRITE
        last_cmd_cycle = first_cmd_cycle + 2 * DRAM_COMMAND_CYCLES - 1;
        bank_free_cycle = last_cmd_cycle + 1 + DRAM_BANK_BUSY_CYCLES;
        data_cycle_start = last_cmd_cycle + 1 + DRAM_BANK_BUSY_CYCLES;
        break;

    case ROW_BUFFER_CONFLICT:
        // PRECHARGE, ACTIVATE, then READ/WRITE
        last_cmd_cycle = first_cmd_cycle + 3 * DRAM_COMMAND_CYCLES - 1;
        bank_free_cycle = last_cmd_cycle + 1 + DRAM_BANK_BUSY_CYCLES;
        data_cycle_start = last_cmd_cycle + 1 + DRAM_BANK_BUSY_CYCLES;
        break;
    }

    uint32_t data_cycle_end = data_cycle_start + DRAM_DATA_TRANSFER_CYCLES - 1;

    // Check all conditions for schedulability
    // 1. Command/address bus must be free for all command cycles
    for (uint32_t c = first_cmd_cycle; c <= last_cmd_cycle; c++) {
        if (c < mc->cmd_bus_free_cycle) {
            return 0;
        }
    }

    // 2. Data bus must be free for all data transfer cycles
    for (uint32_t c = data_cycle_start; c <= data_cycle_end; c++) {
        if (c < mc->data_bus_free_cycle) {
            return 0;
        }
    }

    // 3. Bank must be free
    if (current_cycle < mc->banks[bank].ready_cycle) {
        return 0;
    }

    return 1;
}

// Select best request to schedule using FR-FCFS policy
static MemRequest *select_request_to_schedule(MemController *mc,
                                              uint32_t current_cycle) {
    MemRequest *best = NULL;

    // check all the requests in the queue
    for (uint32_t i = 0; i < mc->queue_capacity; i++) {
        if (!mc->queue[i].valid)
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

        int best_is_hit = (mc->banks[best_bank].has_open_row &&
                           mc->banks[best_bank].open_row == best_row);
        int curr_is_hit = (mc->banks[curr_bank].has_open_row &&
                           mc->banks[curr_bank].open_row == curr_row);

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
static void issue_dram_request(MemController *mc, MemRequest *req,
                               uint32_t current_cycle) {
    uint32_t bank_idx = get_bank_index(req->address);
    uint32_t row = get_row_index(req->address);
    Bank *bank = &mc->banks[bank_idx];

    RowBufferStatus rb_status = get_row_buffer_status(bank, row);

    uint32_t cmd_cycles = 0;

    switch (rb_status) {
    case ROW_BUFFER_HIT:
        cmd_cycles = DRAM_COMMAND_CYCLES;
        break;
    case ROW_BUFFER_MISS:
        cmd_cycles = 2 * DRAM_COMMAND_CYCLES;
        bank->has_open_row = 1;
        bank->open_row = row;
        break;
    case ROW_BUFFER_CONFLICT:
        cmd_cycles = 3 * DRAM_COMMAND_CYCLES;
        bank->has_open_row = 1;
        bank->open_row = row;
        break;
    }

    // Update bus and bank states
    mc->cmd_bus_free_cycle = current_cycle + cmd_cycles;
    bank->ready_cycle = mc->cmd_bus_free_cycle + DRAM_BANK_BUSY_CYCLES;

    // calculate cycle when data transfer starts
    uint32_t data_start = bank->ready_cycle;
    mc->data_bus_free_cycle = data_start + DRAM_DATA_TRANSFER_CYCLES;

    // Calculate when fill will be complete
    // Data arrives at L2 after data transfer + latency back to L2
    uint32_t fill_complete_cycle =
        data_start + DRAM_DATA_TRANSFER_CYCLES + MEM_TO_L2_LATENCY;

    // Update MSHR
    req->mshr->fill_ready_cycle = fill_complete_cycle;
}

void memory_controller_cycle(MemController *mc, uint32_t current_cycle) {
    // First, check for L2 hits that are ready this cycle
    for (size_t i = 0; i < NUM_MSHR; i++) {
        if (mshrs[i].valid && !mshrs[i].done) {
            if (mshrs[i].fill_ready_cycle > 0 &&
                current_cycle >= mshrs[i].fill_ready_cycle) {
                // Fill is ready - mark MSHR as done
                mshrs[i].done = 1;
            }
        }
    }

    // Add new L2 misses to memory request queue
    for (size_t i = 0; i < NUM_MSHR; i++) {
        if (mshrs[i].valid && !mshrs[i].done &&
            mshrs[i].fill_ready_cycle == 0) {
            // Found unqueued L2 miss -> queue it

            // Find free queue slot
            int queued = 0;
            for (uint32_t j = 0; j < mc->queue_capacity; j++) {
                if (!mc->queue[j].valid) {
                    mc->queue[j].address = mshrs[i].address;
                    mc->queue[j].arrival_cycle =
                        current_cycle + L2_TO_MEM_LATENCY;
                    mc->queue[j].from_mem_stage =
                        (mshrs[i].is_icache == 1) ? 0 : 1;
                    mc->queue[j].mshr = &mshrs[i];
                    mc->queue[j].valid = 1;
                    mc->queue_size++;
                    queued = 1;

                    // Mark MSHR with impossible value so we don't queue it
                    // again
                    mshrs[i].fill_ready_cycle = 1;
                    break;
                }
            }

            if (!queued) {
                // Queue full - should not happen with infinite queue
                printf("MEM QUEUE IS FULL! Shouldn't ever happen");
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