#include <stdint.h>
#include <stdlib.h>

#ifndef _CACHE_H_
#define _CACHE_H_

#define DRAM_ACCESS_CYCLES 50

// cache parameters in bytes, 16, 32, 64
#define BLOCK_SIZE 32

#define ICACHE_SIZE (8 * 1024)
#define ICACHE_WAYS 4
#define ICACHE_SETS (ICACHE_SIZE / (BLOCK_SIZE * ICACHE_WAYS))

#define DCACHE_SIZE (64 * 1024)
#define DCACHE_WAYS 8
#define DCACHE_SETS (DCACHE_SIZE / (BLOCK_SIZE * DCACHE_WAYS))

typedef struct Block {
    uint32_t tag, recency; // recency = 0 -> most recently used
    uint8_t valid;         // valid bit (0 = invalid, 1 = valid)
    uint8_t dirty;         // dirty bit (0 = clean, 1 = dirty)

    uint8_t *data; // block_size bytes of data
} Block;

typedef struct Set {
    Block *blocks; // array of blocks
} Set;

// model the cache as a tree, with blocks as leafs
typedef struct Cache {
    uint32_t num_sets;
    uint32_t num_ways;
    uint32_t block_size;
    Set *sets; // array of sets

    // for indexing:
    uint8_t set_bits;
    uint8_t block_bits;
} Cache;

/**
 * @param uint16_t capacity in bytes
 * @param uint8_t block_size in bytes
 */
void alloc_cache(Cache *c, uint32_t capacity, uint8_t block_size,
                 uint8_t num_ways);

/* Release memory dynamically allocated for a cache */
void free_cache(Cache *c);

/* Mark a block withing a set as least recently used */
void update_lru(Cache *c, size_t set, size_t block);

/* retrieve a word of data from cache block, byte by byte */
uint32_t cblock_read_32(Block *block, uint32_t word_start);

/**
 * write a word to cache block byte by byte
 */
void cblock_write_32(Block *block, uint32_t word_start, uint32_t val);

/**
 * copy a cache block from physmem word by word
 * @param uint32_t block_size the block size in bytes.
 * @param uint32_t mem_start start of memory region mapped to block
 */
void cp_mem_to_cblock(Block *block, uint32_t block_size, uint32_t mem_start);

/**
 * copy a cache block's data to physmem word by word
 * @param uint32_t block_size the block size in bytes.
 * @param uint32_t mem_start start of memory region mapped to block
 */
void cp_cblock_to_mem(Block *block, uint32_t block_size, uint32_t mem_start);

/**
 * @param uint32_t address 4 byte aligned adress to access (uint32_t is
 * multiple of 4)
 * @param uint32* if read, read value placed in ptr. if write, ptr to value
 * to be written.
 * @return how many cycles of latency for stall in interval [0,
 * DRAM_ACCESS_CYCLES]
 */
uint32_t cache_access(Cache *c, uint32_t address, uint8_t is_read,
                      uint32_t *val);

#endif
