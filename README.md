# CS4532 Concurrent Programming Lab_01 - Student IDs: 190545H, 190705B

## Overview

This project entails the implementation of a linked list, featuring the Member, Insert, and Delete functions. The program is designed to operate in three different modes:

- **Serial Mode**: A single-threaded execution.
- **Parallel Mode with Mutex**: Multi-threaded execution with a single mutex governing the entire linked list.
- **Parallel Mode with Read-Write Locks**: Multi-threaded execution with read-write locks applied to the entire linked list.

Prior to conducting experiments, the linked list is initialized with 1000 elements, each ranging from 0 to 2^16.

## Usage Instructions

This project was developed and compiled within the CLion IDE. To ensure proper execution, please follow these steps:

1. Open the CMakeLists.txt file and add the following lines:

   ```cmake
   set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

2. Adjust the number of samples (N) as necessary in the main.c file.


With these instructions in place, you can compile and run the program effectively in your chosen development environment.
