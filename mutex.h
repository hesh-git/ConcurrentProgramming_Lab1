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

//Function to be executed by each thread
void *concurrentLinkedListThread(void* thread_rank);

//Struct to hold data related to the concurrent linked list operations
struct concurrent_linked_list_data {
    pthread_mutex_t mutex; //Mutex to lock the linked list
    LinkedList *head; //Head of the linked list

    int m; //Total number of operations to perform

    int member_fraction; //Fraction of member operations
    int insert_fraction; //Fraction of insert operations
    int delete_fraction; //Fraction of delete operations

    int member_opr_count; //Number of member operations performed
    int insert_opr_count; //Number of insert operations performed
    int delete_opr_count; //Number of delete operations performed
    int total_opr_count; //Total number of operations performed
};
typedef struct concurrent_linked_list_data concurrent_linked_list_data;

//Function to execute the concurrent linked list operations
unsigned long executeConcurrentLinkedList(int total_opr, int member_fraction, int insert_fraction, int delete_fraction, int thread_count);

#endif //LAB1_MUTEX_H
