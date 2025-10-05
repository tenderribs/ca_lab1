#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    uint32_t value;   
    struct Node *next;
} Node;

int main() {
    const int NUM_NODES = 16384;
    const int CHASE_COUNT = 100000;

    // Allocate nodes in continuous block
    Node *nodes = (Node *)malloc(NUM_NODES * sizeof(Node));

    // Initialize PRNG with same seed as assembly
    uint32_t random_seed = 7919;

    // Initialize nodes with values and random next pointers
    for (int i = 0; i < NUM_NODES; i++) {
        // Set node value to its index (like assembly)
        nodes[i].value = i;

        // Generate random next pointer using same LCG algorithm
        random_seed = (random_seed * 16807 + 13) & 0x7FFFFFFF;
        int random_index = random_seed % NUM_NODES;

        // Set pointer to another random node (like assembly)
        nodes[i].next = &nodes[random_index];
    }

    // Chase pointers and accumulate values
    Node *current = &nodes[0]; // Start at first node
    uint32_t sum = 0;

    for (int i = 0; i < CHASE_COUNT; i++) {
        sum += current->value;   // Accumulate value
        current = current->next; // Follow pointer to next random node
    }
    printf("sum: %#08x\n", sum);
    
    // Free memory
    free(nodes);
    return 0;
}