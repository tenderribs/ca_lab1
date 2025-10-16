
#ifndef _CACHE_H_
#define _CACHE_H_

#include <stdint.h>
#include <stdlib.h>

#define BLOCK_SIZE 32

#define ICACHE_SIZE (8 * 1024)
#define ICACHE_WAYS 4

#define DCACHE_SIZE (64 * 1024)
#define DCACHE_WAYS 8

#define L2CACHE_SIZE (256 * 1024)
#define L2CACHE_WAYS 16
#define NUM_MSHR 16

#define NUM_BANKS 8
#define NUM_ROWS (64 * 1024)
#define ROW_SIZE (8 * 1024)

typedef enum {
    CACHE_HIT = 0,       // Hit, no stall needed
    CACHE_MISS_WAIT = 1, // Miss, request issued, waiting for fill
    CACHE_NO_MSHR = 2    // Cannot probe L2 (no free MSHRs), should never occur
                         // according to task desc
} CacheAccessResult;

typedef struct Block {
    uint32_t tag;
    uint8_t valid;    // valid bit (0 = invalid, 1 = valid)
    uint32_t recency; // recency = 0 -> most recently used
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

// L2 miss status holding registers
typedef struct MSHR {
    uint32_t address;
    uint8_t valid;             // 1 = entry in use, 0 = free
    uint8_t done;              // 1 = memory fill ready, 0 = still waiting
    uint32_t fill_ready_cycle; // cycle when fill will be ready
    uint8_t is_icache;         // 1 if for icache, 0 if for dcache
} MSHR;

// DRAM bank state
typedef struct Bank {
    uint8_t busy;         // 1 if bank busy, 0 if free
    uint32_t ready_cycle; // cycle when bank becomes ready
    uint32_t open_row;    // currently open row (-1 if closed)
    uint8_t has_open_row; // 1 if row buffer has valid row
} Bank;

/**
 * @param uint16_t capacity in bytes
 * @param uint8_t block_size in bytes
 */
void alloc_cache(Cache *c, uint32_t capacity, uint8_t num_ways,
                 uint8_t block_size);

/* Release memory dynamically allocated for a cache */
void free_cache(Cache *c);

/* Mark a block withing a set as least recently used */
void update_lru(Cache *c, size_t set, size_t block);

/**
 * L1 cache access (instruction or data).
 */
CacheAccessResult l1_cache_access(Cache *c, uint32_t address,
                                  uint8_t is_icache);

/**
 * L2 cache probe (called immediately on L1 miss in same cycle).
 */
CacheAccessResult l2_cache_access(uint32_t address, uint8_t is_icache);

/**
 * Check if a pending L1 cache miss has been filled.
 * Call this each cycle when pipeline is stalled on a cache miss.
 * Returns 1 if fill ready (should unstall next cycle), 0 otherwise.
 */
int check_l1_fill_ready(Cache *c, uint32_t address);

/**
 * Complete the L1 cache fill (insert block into cache).
 * Call this when fill is ready and pipeline is still stalled on it.
 */
void complete_l1_fill(Cache *c, uint32_t address);

// Decl. of global instances
extern Cache icache, dcache, l2cache;
extern MSHR mshrs[NUM_MSHR];

#endif
