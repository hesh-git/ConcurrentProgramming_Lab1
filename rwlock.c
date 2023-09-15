#include "rwlock.h"
#include <stdlib.h>
#include <sys/time.h>
#include "linkedlist.h"
#include "global.h"

unsigned long rwlockExec(int nodes, int total_operations, int member_operations, int insert_operations, int delete_operations, int thread_count){
    int MAX_VAL = 65535;
    int n = nodes;
    rw_lock_data thread_data;
    thread_data.head = NULL;

    thread_data.m = total_operations;
    thread_data.insert_operations_count = 0;
    thread_data.member_operations_count = 0;
    thread_data.delete_operations_count = 0;
    thread_data.total_operations_count = 0;

    thread_data.member_frac = member_operations;
    thread_data.insert_frac = insert_operations;
    thread_data.delete_frac = delete_operations;

    // Randomly insert linked list nodes
    while (n > 0){
        int value = rand()%(MAX_VAL);
        Insert(value, &thread_data.head);
        n--;

    }

    // Initialize the read write lock
    pthread_rwlock_init(&thread_data.rwlock, NULL);
    pthread_mutex_init(&thread_data.count_mutex, NULL);

    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));

    struct timeval start;
    struct timeval end;

    // Start time
    gettimeofday(&start, NULL);

    // Generate threads
    for (int thread=0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, threadFuncReadWrite, (void*) &thread_data);
    }

    for (int thread=0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    // End time
    gettimeofday(&end, NULL);

    pthread_rwlock_destroy(&thread_data.rwlock);
    pthread_mutex_destroy(&thread_data.count_mutex);

    return time_spent(&start, &end);
}

void *threadFuncReadWrite(void* rank){
    int MAX_VAL = 65535;
    rw_lock_data *thread_data = (rw_lock_data*) rank;

    int m = thread_data->m;

    int mMember = thread_data->member_frac;
    int mInsert = thread_data->insert_frac;
    int delete_frac = thread_data->delete_frac;

    while (thread_data->total_operations_count < thread_data->m){

        // Generate random number
        int rand_value = rand() % MAX;

        // Generate random operation number
        int operation = rand() % 3;

        if (operation == 0 && thread_data->insert_operations_count < thread_data->insert_frac){
            if (thread_data->total_operations_count < thread_data->m){
                /* Critical section */
                pthread_rwlock_wrlock(&thread_data->rwlock);
                Insert(rand_value, &thread_data->head);
                thread_data->insert_operations_count++;
                thread_data->total_operations_count++;
                pthread_rwlock_unlock(&thread_data->rwlock);
            }

        }
        else if(operation == 1 && thread_data->delete_operations_count < thread_data->delete_frac){
            if (thread_data->total_operations_count < thread_data->m){
                /* Critical section */
                pthread_rwlock_wrlock(&thread_data->rwlock);
                Delete(rand_value, &thread_data->head);
                thread_data->delete_operations_count++;
                thread_data->total_operations_count++;
                pthread_rwlock_unlock(&thread_data->rwlock);
            }

        }
        else if(thread_data->member_operations_count < thread_data->member_frac){
            if (thread_data->total_operations_count < thread_data->m){
                /* Critical section */
                pthread_rwlock_rdlock(&thread_data->rwlock);
                Member(rand_value, thread_data->head);
                pthread_rwlock_unlock(&thread_data->rwlock);

                /* Critical section (read lock is not suitable for writing) */
                pthread_mutex_lock(&thread_data->count_mutex);
                thread_data->member_operations_count++;
                thread_data->total_operations_count++;
                pthread_mutex_unlock(&thread_data->count_mutex);
            }
        }
    }

    return NULL;
}
