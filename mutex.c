//
// Created by USER on 9/13/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "linkedlist.h"
#include "mutex.h"

unsigned long mutexExec(int total_operations, int member_frac, int insert_frac, int delete_frac, int thread_count){

    mutex_data thread_data;

    thread_data.head = NULL;

    // Total number of operations
    thread_data.m = total_operations;

    // Number of operations run so far
    thread_data.insert_operations_count = 0;
    thread_data.member_operations_count = 0;
    thread_data.delete_operations_count = 0;
    thread_data.total_operations_count = 0;

    // Fractions of each operation
    thread_data.member_frac = member_frac;
    thread_data.insert_frac = insert_frac;
    thread_data.delete_frac = delete_frac;

    int n = 1000; // Number of nodes in linked list
    int nodes = 0;

    // Randomly insert linked list nodes
    while (nodes < n){
        Insert(rand()%MAX, &thread_data.head);
        nodes++;
    }

    // Initialize the mutex
    pthread_mutex_init(&thread_data.mutex, NULL);

    // Allocate memory for threads
    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));

    struct timeval start;
    struct timeval end;

    // Start time
    gettimeofday(&start, NULL);

    // Generate threads
    for (int thread=0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, threadFuncMutex, (void*) &thread_data);
    }

    for (int thread=0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    // End time
    gettimeofday(&end, NULL);

    pthread_mutex_destroy(&thread_data.mutex);

    unsigned long time = time_spent(&start, &end);
    //printf("Time taken: %lu μs\n", time);

    Destroy(thread_data.head);
    printf("Mutex run complete\n");
    return time;
}

void *threadFuncMutex(void * args){

    mutex_data* thread_data = args;

    while (thread_data->total_operations_count < thread_data->m){

        // Generate random number
        int rand_value = rand() % MAX;

        // Generate random operation number
        int op = rand() % 3;

        if (op==0 && thread_data->insert_operations_count < thread_data->insert_frac){
            if (thread_data->total_operations_count < thread_data->m){
                /* Critical section */
                pthread_mutex_lock(&thread_data->mutex);
                Insert(rand_value, &thread_data->head);
                thread_data->insert_operations_count++;
                thread_data->total_operations_count++;
                pthread_mutex_unlock(&thread_data->mutex);
            }
        }
        else if(op==1 && thread_data->delete_operations_count < thread_data->delete_frac){
            if (thread_data->total_operations_count < thread_data->m){
                /* Critical section */
                pthread_mutex_lock(&thread_data->mutex);
                Delete(rand_value, &thread_data->head);
                thread_data->delete_operations_count++;
                thread_data->total_operations_count++;
                pthread_mutex_unlock(&thread_data->mutex);
            }
        }
        else if(thread_data->member_operations_count < thread_data->member_frac){
            if (thread_data->total_operations_count < thread_data->m){
                /* Critical section */
                pthread_mutex_lock(&thread_data->mutex);
                Member(rand_value, thread_data->head);
                thread_data->member_operations_count++;
                thread_data->total_operations_count++;
                pthread_mutex_unlock(&thread_data->mutex);
            }
        }
    }
    return NULL;
}

