
#ifndef CONCURRENTPROGRAMMING_LAB1_RWLOCK_H
#define CONCURRENTPROGRAMMING_LAB1_RWLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "linkedlist.h"
#include "global.h"

void *threadFuncReadWrite(void* rank);

struct rw_lock_data {
    pthread_rwlock_t rwlock;
    pthread_mutex_t count_mutex;
    struct list_node_s *head;

    int m;

    int member_frac;
    int insert_frac;
    int delete_frac;

    int member_operations_count;
    int insert_operations_count;
    int delete_operations_count;
    int total_operations_count;
};
typedef struct rw_lock_data rw_lock_data;

unsigned long rwlockExec(int nodes, int total_operations, int member_operations, int insert_operations, int delete_operations, int thread_count);

#endif //CONCURRENTPROGRAMMING_LAB1_RWLOCK_H
