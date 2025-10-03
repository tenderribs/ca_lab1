#include "cache.h"
#include "shell.h"
#include <assert.h>

void alloc_cache(Cache *c, uint32_t capacity, uint8_t block_size,
                 uint8_t num_ways) {
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
            block->dirty = 0;
            block->recency = b;
            block->data = malloc(sizeof(uint32_t) * c->block_size);
        }
    }
}

void free_cache(Cache *c) {
    // free the blocks in each set
    for (size_t s = 0; s < c->num_sets; s++) {
        // free data
        free(c->sets[s].blocks->data);

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

uint32_t cblock_read_32(Block *block, uint32_t word_start) {
    return (
        block->data[word_start + 3] << 24 | block->data[word_start + 2] << 16 |
        block->data[word_start + 1] << 8 | block->data[word_start + 0] << 0);
}

void cblock_write_32(Block *block, uint32_t word_start, uint32_t val) {
    block->data[word_start + 3] = (val >> 24) & 0xFF;
    block->data[word_start + 2] = (val >> 16) & 0xFF;
    block->data[word_start + 1] = (val >> 8) & 0xFF;
    block->data[word_start + 0] = (val >> 0) & 0xFF;
}

void cp_mem_to_cblock(Block *block, uint32_t block_size, uint32_t mem_start) {
    // insert bytes into block, word by word
    for (size_t word = 0; word < (block_size / 4); word++) {
        // first load word from mem
        uint32_t from_mem = mem_read_32(mem_start + word * 4);

        // then separate word into bytes, place in block
        block->data[word * 4 + 0] = (from_mem >> 0) & 0xFF;
        block->data[word * 4 + 1] = (from_mem >> 8) & 0xFF;
        block->data[word * 4 + 2] = (from_mem >> 16) & 0xFF;
        block->data[word * 4 + 3] = (from_mem >> 24) & 0xFF;
    }
}

void cp_cblock_to_mem(Block *block, uint32_t block_size, uint32_t mem_start) {
    // combine individual bytes into word, then write to physmem
    for (size_t word = 0; word < (block_size / 4); word++) {
        uint32_t write_data =
            (block->data[word * 4 + 3] << 24 | block->data[word * 4 + 2] << 16 |
             block->data[word * 4 + 1] << 8 | block->data[word * 4 + 0] << 0);

        mem_write_32(mem_start, write_data);
    }
}

uint32_t cache_access(Cache *c, uint32_t address, uint8_t is_read,
                      uint32_t *val) {
    assert((address % 4 == 0) && "Address should be multiple of 4 bytes");

    // calculate the set index and the tag
    uint32_t tag = (address >> (c->block_bits + c->set_bits));
    uint32_t set = ((address >> c->block_bits) & ((1 << c->set_bits) - 1));

    // 4 byte aligned start pos where we shall access the word in the block
    uint32_t word_start = (address & ((1 << c->block_bits) - 1)) & ~3;

    // starting address of memory region that gets mapped to cblock
    uint32_t block_mem_start_addr = (address & ~((1 << c->block_bits) - 1));

    // check set for any hits in set
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].tag == tag && c->sets[set].blocks[b].valid) {

            // HIT cuz tag matches and block is valid
            // -> update LRU positions of set's blocks
            update_lru(c, set, b);

            if (is_read) {
                // read the word held inside cache blocks
                *val = cblock_read_32(&c->sets[set].blocks[b], word_start);

                return 0;
            } else {
                // write value to cblock
                cblock_write_32(&c->sets[set].blocks[b], word_start, *val);
                c->sets[set].blocks[b].dirty = 1;

                // write through policy for now, so write cblock directly to mem
                cp_cblock_to_mem(&c->sets[set].blocks[b], c->block_size,
                                 block_mem_start_addr);
                c->sets[set].blocks[b].dirty = 0;

                // write through's write causes stall
                return DRAM_ACCESS_CYCLES;
            }
        }
    }

    // miss, so need to update a block somewhere in the set

    // 1. look for invalid blocks we can just fill up for first time, exit early
    for (size_t b = 0; b < c->num_ways; b++) {
        if (!c->sets[set].blocks[b].valid) {
            // found empty block, initialize it
            c->sets[set].blocks[b].tag = tag;
            c->sets[set].blocks[b].dirty = 0;
            c->sets[set].blocks[b].valid = 1;
            update_lru(c, set, b);

            // transfer the block of bytes from physmem to the empty cache block
            cp_mem_to_cblock(&c->sets[set].blocks[b], c->block_size,
                             block_mem_start_addr);

            // then make use of loaded block
            if (is_read) {
                // read the loaded block in cache
                *val = cblock_read_32(&c->sets[set].blocks[b], word_start);
            } else {
                // write val to cache block
                cblock_write_32(&c->sets[set].blocks[b], word_start, *val);
                c->sets[set].blocks[b].dirty = 1;

                // write cblock directly to mem due to write-through policy
                cp_cblock_to_mem(&c->sets[set].blocks[b], c->block_size,
                                 block_mem_start_addr);
                c->sets[set].blocks[b].dirty = 0;
            }

            return DRAM_ACCESS_CYCLES;
        }
    }

    // 2. blocks all valid, so evict the oldest block in set
    for (size_t b = 0; b < c->num_ways; b++) {
        if (c->sets[set].blocks[b].recency == (c->num_ways - 1)) {
            // found oldest block, replace it
            c->sets[set].blocks[b].tag = tag;
            c->sets[set].blocks[b].dirty = 0;
            c->sets[set].blocks[b].valid = 1;
            update_lru(c, set, b);

            // transfer the block of bytes from physmem to the empty cache block
            cp_mem_to_cblock(&c->sets[set].blocks[b], c->block_size,
                             block_mem_start_addr);

            if (is_read) {
                // read the loaded block in cache
                *val = cblock_read_32(&c->sets[set].blocks[b], word_start);
            } else {
                // write val to cache block
                cblock_write_32(&c->sets[set].blocks[b], word_start, *val);
                c->sets[set].blocks[b].dirty = 1;

                // write cblock directly to mem due to write-through policy
                cp_cblock_to_mem(&c->sets[set].blocks[b], c->block_size,
                                 block_mem_start_addr);
                c->sets[set].blocks[b].dirty = 0;
            }

            return DRAM_ACCESS_CYCLES;
        }
    }

    // have to stall because of the cache miss
    return DRAM_ACCESS_CYCLES;
}
