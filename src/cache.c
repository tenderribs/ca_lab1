#include "cache.h"
#include "shell.h"
#include <assert.h>
#include <stdlib.h>

#define DRAM_ACCESS_CYCLES 50

#define IMMEDIATE_RRPV 0
#define LONG_RRPV 2
#define DISTANT_RRPV 3

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
#ifdef LRU
            block->recency = b;
#endif
#ifdef RRIP
            block->rrpv = LONG_RRPV;
#endif
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

#ifdef LRU
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
#endif

#ifdef RRIP
void update_rrip(Cache *c, size_t set, size_t block) {
    c->sets[set].blocks[block].rrpv = IMMEDIATE_RRPV;
}

#endif

uint32_t cache_access(Cache *c, uint32_t address) {
    assert((address % 4 == 0) && "Address should be multiple of 4 bytes");

    // calculate the set index and the tag
    uint32_t tag = (address >> (c->block_bits + c->set_bits));
    uint32_t set = ((address >> c->block_bits) & ((1 << c->set_bits) - 1));

    // check set for any hits in set
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].tag == tag && c->sets[set].blocks[b].valid) {
            // HIT since tag matches and block is valid
            // -> update LRU positions of set's blocks
#ifdef LRU
            update_lru(c, set, b);
#endif
#ifdef RRIP
            update_rrip(c, set, b);
#endif
            return 0;
        }
    }

    // miss, so need to update a block somewhere in the set

    size_t victim = 0;
    size_t found = 0;

    // 1. look for invalid blocks we can just fill up for first time, exit early
    for (size_t b = 0; b < c->num_ways; b++) {
        if (!c->sets[set].blocks[b].valid) {
            victim = b;
            found = 1;
            break;
        }
    }

    // 2. blocks all valid, so replace a block

#ifdef RAND
    // random policy chooses random block in set
    if (!found) {
        victim = rand() % c->num_ways;
    }
#endif

#ifdef LRU
    if (!found) {
        // LRU chooses the least recently used block
        for (size_t b = 0; b < c->num_ways; b++) {
            if (c->sets[set].blocks[b].recency == (c->num_ways - 1)) {
                victim = b;
                break;
            }
        }
    }
#endif

#ifdef RRIP
    // https://people.csail.mit.edu/emer/media/papers/2010.06.isca.rrip.pdf

    // Modify victim selection in cache_access:
    if (!found) {
        // Find a block with RRPV = DISTANT_RRPV
        int found_victim = 0;
        while (!found_victim) {
            for (size_t b = 0; b < c->num_ways; b++) {
                if (c->sets[set].blocks[b].rrpv == DISTANT_RRPV) {
                    victim = b;
                    found_victim = 1;
                    break;
                }
            }

            // If no DISTANT_RRPV found, increment all RRPVs and try again
            if (!found_victim) {
                for (size_t b = 0; b < c->num_ways; b++) {
                    if (c->sets[set].blocks[b].valid &&
                        c->sets[set].blocks[b].rrpv < DISTANT_RRPV) {
                        c->sets[set].blocks[b].rrpv++;
                    }
                }
            }
        }
    }
    // New blocks inserted with LONG_RRPV
    c->sets[set].blocks[victim].rrpv = LONG_RRPV;
#endif

    // replace victim block
    c->sets[set].blocks[victim].tag = tag;
    c->sets[set].blocks[victim].valid = 1;

#ifdef LRU
    update_lru(c, set, victim);
#endif
#ifdef RRIP
    update_rrip(c, set, victim);
#endif
    return DRAM_ACCESS_CYCLES;
}