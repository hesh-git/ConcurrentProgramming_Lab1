//
// Created by USER on 9/13/2023.
//

#ifndef LAB1_MUTEX_H
#define LAB1_MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "linkedlist.h"
#include "global.h"

void *threadFuncMutex(void* rank);

struct mutex_data {
    pthread_mutex_t mutex;
    LinkedList *head;

    int m;

    int member_frac;
    int insert_frac;
    int delete_frac;

    int member_operations_count;
    int insert_operations_count;
    int delete_operations_count;
    int total_operations_count;
};
typedef struct mutex_data mutex_data;

unsigned long mutexExec(int total_operations, int member_frac, int insert_frac, int delete_frac, int thread_count);

#endif //LAB1_MUTEX_H
