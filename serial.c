#include <stdlib.h>
#include "serial.h"
#include <sys/time.h>
#include "linkedlist.h"
#include "global.h"

unsigned long serialExec(int nodes, int total_operations, int member_operations, int insert_operations, int delete_operations){
    int MAX_VAL = 65535;
    int n = nodes;
    int m = total_operations;
    int mMember = member_operations;
    int mInsert = insert_operations;
    int mDelete = delete_operations;
    LinkedList list;
    InitList(&list);

    //Populate the linked list with random values
    while (n > 0){
        int value = rand()%(MAX_VAL);
        if(!Member(value, list.head)){
            Insert(value, &list.head);
            n--;
        }
    }

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    // Perform Member, Insert, and Delete operations
    while (m > 0){
        int value = rand()%(MAX_VAL);
        int operation = rand()%3;
        if(operation == 0 && mMember > 0){
            Member(value, list.head);
            mMember--;
            m--;
        }
        else if(operation == 1 && mInsert > 0){
            Insert(value, &list.head);
            mInsert--;
            m--;
        }
        else if(operation == 2 && mDelete > 0){
            Delete(value, &list.head);
            mDelete--;
            m--;
        }
    }
    gettimeofday(&end, NULL);

    return time_spent(&start, &end);

}
