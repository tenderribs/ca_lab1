#include <stdint.h>

typedef struct Node {
    uint32_t value;
    struct Node *next;
} Node;

// Static allocation in global space
#define NUM_NODES 16384
#define CHASE_COUNT 100000
static Node nodes[NUM_NODES];

int main() {
    // Initialize PRNG with same seed as assembly
    uint32_t random_seed = 7919;

    // Initialize nodes with values and random next pointers
    for (int i = 0; i < NUM_NODES; i++) {
        nodes[i].value = i;

        // Generate random next pointer using MINSTD LCG algorithm
        // https://en.wikipedia.org/wiki/Lehmer_random_number_generator
        random_seed = (random_seed * 16807) & 0x7FFFFFFF;
        int random_index = random_seed % NUM_NODES;

        nodes[i].next = &nodes[random_index];
    }

    // Pointer-chasing loop
    Node *current = &nodes[0];
    volatile uint32_t sum = 0; // volatile so -03 gcc flag doesn't optimize away

    for (int i = 0; i < CHASE_COUNT; i++) {
        sum += current->value;
        current = current->next;
    }

    return 0;
}