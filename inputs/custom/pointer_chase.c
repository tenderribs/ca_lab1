#include "stdio.h"
#include <stdint.h>

#define NUM_NODES (32 * 1024)
#define CHASE_COUNT 100000

int main() {
    uint16_t nodes[NUM_NODES];

    // Initialize PRNG with same seed as assembly
    uint32_t random_seed = 1337;
    const uint32_t A = 48271;

    // // double check size of nodes
    // printf("sizeof(nodes): %lu", sizeof(nodes));

    // Initialize nodes with values and random next pointers
    for (int i = 0; i < NUM_NODES; i++) {

        // Generate random next pointer using MINSTD LCG algorithm
        // https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
        // https://en.wikipedia.org/wiki/Lehmer_random_number_generator#Sample_C99_code

        // to avoid 64 bit arithmetic, use legit same code as example in
        // wikipedia max: 32,767 * 48,271 = 1,581,695,857 = 0x5e46c371
        uint32_t low = (random_seed & 0x7fff) * A;
        // max: 65,535 * 48,271 = 3,163,439,985 = 0xbc8e4371
        uint32_t high = (random_seed >> 15) * A;
        // max: 0x5e46c371 + 0x7fff8000 + 0xbc8e = 0xde46ffff
        uint32_t x = low + ((high & 0xffff) << 15) + (high >> 16);

        random_seed = (x & 0x7fffffff) + (x >> 31);

        int random_index = random_seed % NUM_NODES;

        nodes[i] = random_index;

        // // to check distribution for actual randomness
        // printf("%d, %d\r\n", i + 1, random_index);
    }

    // Pointer-chasing loop
    volatile uint32_t sum = 0; // volatile so -03 gcc flag doesn't optimize away

    uint32_t curr = nodes[0];
    for (int i = 0; i < CHASE_COUNT; i++) {
        sum += curr;
        curr = nodes[curr]; // go to next
    }

    return 0;
}