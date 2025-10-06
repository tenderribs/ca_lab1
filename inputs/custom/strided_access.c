#include <stdio.h>

#define ARRAY_SIZE 65536  // 64K elements
#define NUM_ITERATIONS 10

int main() {
    int array[ARRAY_SIZE];
    volatile int sum = 0;  // volatile to prevent godbolt opt
    
    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    
    // Test different strides
    for (int stride = 1; stride <= 128; stride *= 2) {
        sum = 0;
        
        // Access with current stride
        for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
            for (int i = 0; i < ARRAY_SIZE; i += stride) {
                sum += array[i];
            }
        }
    }
    
    return 0;
}