#include <stdio.h>
#include "linkedlist.h"
#include "serial.h"
#include "rwlock.h"
#include <math.h>


FILE* createAndOpenCSVFile(const char* filename);

int main() {

    const int N = 400;

    // Number of operations
    int m = 10000;
    int n = 1000; // Number of nodes in linked list

    // Fractions for each case
    int member_frac;
    int insert_frac;
    int delete_frac;

    // Use current time as seed for random generator
    srand(time(0));

    int cases[] = {0, 1, 2};
    double fractions[][3] = {{0.99, 0.005, 0.005}, {0.90, 0.05, 0.05}, {0.50, 0.25, 0.25}};
    const char* filenames[] = {
            "C:\\Users\\ASUS\\Documents\\Sem 7\\Concurrent Programming\\Labs\\ConcurrentProgramming_Lab1\\output\\Case_1.csv",
            "C:\\Users\\ASUS\\Documents\\Sem 7\\Concurrent Programming\\Labs\\ConcurrentProgramming_Lab1\\output\\Case_2.csv",
            "C:\\Users\\ASUS\\Documents\\Sem 7\\Concurrent Programming\\Labs\\ConcurrentProgramming_Lab1\\output\\Case_3.csv"
    };

    for (int i = 0; i < 3; i++) {
        FILE *file = createAndOpenCSVFile(filenames[i]);
        if (file == NULL) {
            printf("Error opening file for case %d\n", cases[i]);
            continue;
        }

        member_frac = fractions[i][0] * m;
        insert_frac = fractions[i][1] * m;
        delete_frac = fractions[i][2] * m;

        printf("Member: %d, Insert: %d, Delete: %d\n", member_frac, insert_frac, delete_frac);

        // Perform operations for the current case here
        unsigned long total_runtime = 0;
        unsigned long total_rw_t1_runtime = 0;
        unsigned long total_rw_t2_runtime = 0;
        unsigned long total_rw_t4_runtime = 0;
        unsigned long total_rw_t8_runtime = 0;
        for(int j = 0; j < N; j++) {
            unsigned long serial_runtime = serialExec(n,m, member_frac, insert_frac, delete_frac);

            unsigned long rw_t1_runtime = rwlockExec(n,m, member_frac, insert_frac, delete_frac, 1);
            unsigned long rw_t2_runtime = rwlockExec(n,m, member_frac, insert_frac, delete_frac, 2);
            unsigned long rw_t4_runtime = rwlockExec(n,m, member_frac, insert_frac, delete_frac, 4);
            unsigned long rw_t8_runtime = rwlockExec(n,m, member_frac, insert_frac, delete_frac, 8);
            //write to serial runtime column in csv file
            total_runtime += serial_runtime;
            total_rw_t1_runtime += rw_t1_runtime;
            total_rw_t2_runtime += rw_t2_runtime;
            total_rw_t4_runtime += rw_t4_runtime;
            total_rw_t8_runtime += rw_t8_runtime;
        }
        double avg_serial_runtime = total_runtime / N;
        double avg_rw_t1_runtime = total_rw_t1_runtime / N;
        double avg_rw_t2_runtime = total_rw_t2_runtime / N;
        double avg_rw_t4_runtime = total_rw_t4_runtime / N;
        double avg_rw_t8_runtime = total_rw_t8_runtime / N;
        //print average runtime for each case in seconds
        printf("Average serial runtime: %f ms\n", avg_serial_runtime/1000);
        printf("Average rw_t1 runtime: %f ms\n", avg_rw_t1_runtime/1000);
        printf("Average rw_t2 runtime: %f ms\n", avg_rw_t2_runtime/1000);
        printf("Average rw_t4 runtime: %f ms\n", avg_rw_t4_runtime/1000);
        printf("Average rw_t8 runtime: %f ms\n", avg_rw_t8_runtime/1000);
        printf("=====================================================\n");
        //Get standard deviation

        fclose(file); // Close the file when done with it
    }

    return 0;

}

// Function to create and open a CSV file with a given filename and write headers
FILE* createAndOpenCSVFile(const char* filename) {
    FILE* file = fopen(filename, "w+");
    if (file != NULL) {
        fprintf(file, "Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, RWLock_t1, RWLock_t2, RWLock_t4, RWLock_t8\n");
    }
    return file;
}



