# MEMORY MANAGEMENT

Code Simulates a memory management unit (MMU) servising multiple processes (modeled as threads).

Two main entities:

1. **Process:** Simulates a process with 32 registers, a fixed virtual memory size, and a sequence of R/W operations to request from the MMU.

2. **MMU:** Manages memory for the processes. It has a fixed page size, main memory size, and a disk size big enough to fit all virtual addresses. MMU translates VA to PA, fills main memory with requested processes pages, and evicts pages to disk when necessary using the clock algorithm.

## Build

    make

## Run

    ./main <input file name> <output file name>
