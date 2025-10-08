#include <stdint.h>

#define HOT_SIZE 2048           // 8KB - repeatedly accessed "hot" data
#define STREAM_SIZE (32 * 1024) // 128KB - streaming data accessed once
#define ITERATIONS 20 // don't go too overboard on this param, takes long

int main() {
    uint32_t hot_data[HOT_SIZE];       // Frequently reused
    uint32_t stream_data[STREAM_SIZE]; // One-time scan (should be evicted
                                       // immediately)

    // Initialize
    for (uint32_t i = 0; i < HOT_SIZE; i++) {
        hot_data[i] = i;
    }
    for (uint32_t i = 0; i < STREAM_SIZE; i++) {
        stream_data[i] = i;
    }

    volatile uint32_t sum = 0;

    for (uint32_t iter = 0; iter < ITERATIONS; iter++) {

        // Access hot data multiple times (high reuse)
        for (uint32_t rep = 0; rep < 5; rep++) {
            for (uint32_t i = 0; i < HOT_SIZE; i++) {
                sum += hot_data[i];
            }
        }

        // Stream through cold data ONCE (no reuse - should evict immediately)
        for (uint32_t i = 0; i < STREAM_SIZE; i++) {
            sum += stream_data[i];
        }
    }
}