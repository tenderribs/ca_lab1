#include "cache.h"
#include "shell.h"
#include <assert.h>

#define DRAM_ACCESS_CYCLES 50

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
            block->recency = b;
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

    // increment the recency for valid blocks that were more recent than current
    // one
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].valid &&
            c->sets[set].blocks[b].recency < prev_recency) {
            c->sets[set].blocks[b].recency++;
        }
    }

    // and most recently updated block gets the lru pos 0;
    c->sets[set].blocks[block].recency = 0;
}

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
            update_lru(c, set, b);

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
            break;
        }
    }

    if (!found) {
        // 2. blocks all valid, so evict the oldest block in set
        for (size_t b = 0; b < c->num_ways; b++) {
            if (c->sets[set].blocks[b].recency == (c->num_ways - 1)) {
                victim = b;
                break;
            }
        }
    }

    // found empty block, initialize it
    c->sets[set].blocks[victim].tag = tag;
    c->sets[set].blocks[victim].valid = 1;
    update_lru(c, set, victim);

    return DRAM_ACCESS_CYCLES;
}
