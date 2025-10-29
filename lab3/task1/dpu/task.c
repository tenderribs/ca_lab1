/*
* AXPY with multiple tasklets
*
*/
#include <stdint.h>
#include <stdio.h>
#include <defs.h>
#include <mram.h>
#include <alloc.h>
#include <perfcounter.h>
#include <barrier.h>

#include "../support/common.h"

// Holds 64MB (as 8M int64_t) to hold transferred data
__mram_noinit T dpu_buffer[(8 * 1024 * 1024)];

// Input and output arguments
__host dpu_arguments_t DPU_INPUT_ARGUMENTS;

// Barrier
BARRIER_INIT(my_barrier, NR_TASKLETS);

extern int main_kernel1(void);
int (*kernels[nr_kernels])(void) = {main_kernel1};
int main(void) {
    // Kernel
    return kernels[DPU_INPUT_ARGUMENTS.kernel]();
}

// main_kernel1
int main_kernel1() {
    unsigned int tasklet_id = me();

    // nonsensical reference to dpu_buffer to prevent compiler optimization
    // and subsequent symbol not found error in host code
    dpu_buffer[0] = dpu_buffer[0];

#if PRINT
    printf("tasklet_id = %u\n", tasklet_id);
#endif

    if (tasklet_id == 0){
        mem_reset(); // Reset the heap
    }
    // Barrier
    barrier_wait(&my_barrier);

    return 0;
}
