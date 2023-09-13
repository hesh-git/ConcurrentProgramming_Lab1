//
// Created by ASUS on 9/13/2023.
//

#ifndef CONCURRENTPROGRAMMING_LAB1_LINKEDLIST_H
#define CONCURRENTPROGRAMMING_LAB1_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct list_node_s {
    int data;
    struct list_node_s* next;
};

typedef struct {
    struct list_node_s* head;
}LinkedList;

int Member(int value, struct list_node_s* head_p);
int Insert(int value, struct list_node_s** head_pp);
int Delete(int value, struct list_node_s** head_pp);
void InitList(LinkedList* list);
int GetSize(LinkedList* list);
void PrintList(LinkedList* list);
void Destroy(struct list_node_s* head_p);

#endif //CONCURRENTPROGRAMMING_LAB1_LINKEDLIST_H
