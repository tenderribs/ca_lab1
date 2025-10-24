#ifndef _MEM_CONTROLLER_H_
#define _MEM_CONTROLLER_H_

#include "pipe.h"
#include <stdint.h>

// DRAM timing constants (in cycles)
#define CMD_CYCLES 4
#define BANK_BUSY_CYCLES 100
#define DATA_TF_CYCLES 50

#define L2_TO_MEM_LATENCY 5
#define MEM_TO_L2_LATENCY 5

typedef enum { ROW_BUFFER_HIT, ROW_BUFFER_MISS, ROW_BUFFER_CONFLICT } RowBufferStatus;

// DRAM bank state
typedef struct Bank {
    uint32_t req_start;   // cycle when bank started serving the request
    uint32_t open_row;    // currently open row (-1 if closed)
    uint8_t has_open_row; // 1 if row buffer has valid row
    uint8_t num_commands; // 1, 2, or 3, number of cmds for req
} Bank;

// Memory request in queue
typedef struct MemRequest {
    uint32_t address;
    uint32_t arrival_cycle; // cycle when request arrived in DRAM
    uint8_t from_mem_stage; // 1 if from MEM stage, 0 if from fetch
    MSHR *mshr;             // pointer to associated MSHR
    uint8_t valid;          // 1 if entry valid
} MemRequest;

// Memory controller state
typedef struct MemController {
    MemRequest *queue;            // request queue (dynamically allocated)
    uint32_t queue_capacity;      // max queue size
    uint32_t queue_size;          // current number of requests
    uint32_t cmd_bus_free_cycle;  // cycle when cmd/addr bus becomes free
    uint32_t data_bus_free_cycle; // cycle when data bus becomes free
    Bank *banks;
} MemController;

void init_memory_controller(MemController *mc, uint32_t queue_capacity);

void free_memory_controller(MemController *mc);

/**
 * Simulate one cycle of memory controller operation.
 * This processes pending requests, issues DRAM commands, handles fills.
 */
void memory_controller_cycle(MemController *mc, uint32_t current_cycle);

// Decl. of global instances
extern MSHR mshrs[NUM_MSHR];

#endif