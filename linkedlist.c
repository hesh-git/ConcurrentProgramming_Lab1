#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <pthread.h>

//Initialize the linked list
void InitList(LinkedList* list){
    list->head = NULL;
}

//Check if value is in the linked list
int Member(int value, struct list_node_s* head_p) {
    struct list_node_s *curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value)
        return 0;
    else
        return 1;
}

//Insert value into the linked list
int Insert(int value, struct list_node_s** head_pp){
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL)
            *head_pp = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    } else {
        return 0;
    }
}

//Delete value from the linked list
int Delete(int value, struct list_node_s** head_pp){
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value){
        if (pred_p == NULL){
            *head_pp = curr_p->next;
            free(curr_p);
        } else {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    } else {
        return 0;
    }

}

//get linked list size
int GetSize(LinkedList* list){
    struct list_node_s* curr_p = list->head;
    int size = 0;
    while (curr_p != NULL){
        size++;
        curr_p = curr_p->next;
    }
    return size;
}

void PrintList(LinkedList* list){
    struct list_node_s* curr_p = list->head;
    while (curr_p != NULL){
        printf("%d ", curr_p->data);
        curr_p = curr_p->next;
    }
    printf("NULL\n");
}

//Destroy the linked list
void Destroy(struct list_node_s* head_p){
    struct list_node_s* curr_p = head_p;
    struct list_node_s* temp_p;

    while (curr_p != NULL){
        temp_p = curr_p;
        curr_p = curr_p->next;
        free(temp_p);
    }
}