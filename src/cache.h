#include <stdint.h>
#include <stdlib.h>

#ifndef _CACHE_H_
#define _CACHE_H_

#define BLOCK_SIZE 32

#define ICACHE_SIZE (8 * 1024)
#define ICACHE_WAYS 4

#define DCACHE_SIZE (64 * 1024)
#define DCACHE_WAYS 8

// select caching policy
#define RAND
// #define LRU
// #define RRIP // 2-bit Static RRIP

typedef struct Block {
    uint32_t tag;
    uint8_t valid; // valid bit (0 = invalid, 1 = valid)
#ifdef LRU
    uint32_t recency; // recency = 0 -> most recently used
#endif
#ifdef RRIP
    uint32_t rrpv; // reference prediction values
#endif
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
void alloc_cache(Cache *c, uint32_t capacity, uint8_t num_ways,
                 uint8_t block_size);

/* Release memory dynamically allocated for a cache */
void free_cache(Cache *c);

#ifdef LRU
/* Mark a block withing a set as least recently used */
void update_lru(Cache *c, size_t set, size_t block);
#endif

#ifdef RRIP
void update_rrip(Cache *c, size_t set, size_t block);
#endif

/**
 * @param uint32_t address 4 byte aligned adress to access
 * @return how many cycles of latency for stall in interval [0,
 * DRAM_ACCESS_CYCLES]
 */
uint32_t cache_access(Cache *c, uint32_t address);

#endif
