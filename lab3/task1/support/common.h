#ifndef _COMMON_H_
#define _COMMON_H_

#define XSTR(x) STR(x)
#define STR(x) #x

// Data type
#define T int64_t
#define DIV 3 // Shift right to divide by sizeof(T)

// Maximum buffer size per DPU (in elements)
// This should be large enough to hold the maximum expected data per DPU
// For example: 64MB MRAM / sizeof(T) = 64MB / 8 bytes = 8M elements

#define DPU_BUFFER dpu_mram_buffer
#define BUFFER_SIZE (8 * 1024 * 1024) // 8M elements (64MB for int64_t)

// Structures used by both the host and the dpu to communicate information
typedef struct {
    uint32_t size;
    uint32_t transfer_size;
	enum kernels {
	    kernel1 = 0,
	    nr_kernels = 1,
	} kernel;
} dpu_arguments_t; // Input arguments

typedef struct {
    uint64_t count;
} dpu_results_t; // Results (cycle count)

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define divceil(n, m) (((n)-1) / (m) + 1)
#define roundup(n, m) ((n / m) * m + m)
#endif
