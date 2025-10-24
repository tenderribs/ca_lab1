#include "cache.h"
#include "shell.h"
#include "stdio.h"
#include <assert.h>
#include <stdlib.h>

void alloc_cache(Cache *c, uint32_t capacity, uint8_t num_ways, uint8_t block_size) {
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

    // dynamically allocate zeroed memory for cache
    c->sets = (Set *)calloc(c->num_sets, sizeof(Set));

    for (size_t s = 0; s < c->num_sets; s++) {
        c->sets[s].blocks = (Block *)calloc(c->num_ways, sizeof(Block));
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
        if (c->sets[set].blocks[b].valid && c->sets[set].blocks[b].recency < prev_recency) {
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
        if (mshrs[i].valid && (mshrs[i].address & ~(BLOCK_SIZE - 1)) == block_addr) {
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

CacheAccessResult l1_cache_access(Cache *c, uint32_t address, uint8_t is_icache) {
    assert((address % 4 == 0) && "Address should be multiple of 4 bytes");

    // calculate the L1 set index and the tag
    uint32_t tag = (address >> (c->block_bits + c->set_bits));
    uint32_t set = ((address >> c->block_bits) & ((1 << c->set_bits) - 1));

    // check L1 set for any hits in set
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].tag == tag && c->sets[set].blocks[b].valid) {
            // HIT since tag matches and block is valid
            // -> update LRU positions of set's blocks
            printf("Hit L1 cache\r\n");

            update_lru(c, set, b);
            return CACHE_HIT;
        }
    }

    printf("MISSED L1 cache\r\n");

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
    printf("ACCESS L2 cache\r\n");

    // L2 cache can only be probed if there are free MSHRs
    MSHR *mshr = allocate_mshr(address, is_icache);
    if (mshr == NULL) {
        return CACHE_NO_MSHR;
    }

    // calculate the L2 set index and the tag
    uint32_t tag = (address >> (l2cache.block_bits + l2cache.set_bits));
    uint32_t set = ((address >> l2cache.block_bits) & ((1 << l2cache.set_bits) - 1));

    // check L2 set for any hits in set
    for (size_t b = 0; b < l2cache.num_ways; b++) {
        if (l2cache.sets[set].blocks[b].tag == tag && l2cache.sets[set].blocks[b].valid) {
            // L2 HIT - will send fill notification after 15 cycles
            update_lru(&l2cache, set, b);

            printf("L2 HIT\r\n");

            // Mark when fill will be ready (current cycle is in shell.c
            // stat_cycles)
            extern uint32_t stat_cycles;
            mshr->fill_ready_cycle = stat_cycles + L2_HIT_LATENCY;

            return CACHE_MISS_WAIT; // Not truly a miss, but L1 still waits for fill
        }
    }

    printf("L2 MISS\r\n");

    // L2 MISS - need to go to memory
    // Add request to memory controller queue (will be done in memory_controller_cycle) The memory
    // controller will set mshr->done when data is ready
    return CACHE_MISS_WAIT;
}

void insert_l2_block(uint32_t address) {
    uint32_t tag = (address >> (l2cache.block_bits + l2cache.set_bits));
    uint32_t set = ((address >> l2cache.block_bits) & ((1 << l2cache.set_bits) - 1));

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