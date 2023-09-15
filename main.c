#include <stdio.h>
#include "linkedlist.h"
#include "serial.h"
#include <math.h>


// Function to create and open a CSV file with a given filename and write headers
FILE* createAndOpenCSVFile(const char* filename) {
    FILE* file = fopen(filename, "w+");
    if (file != NULL) {
        fprintf(file, "Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, RWLock_t1, RWLock_t2, RWLock_t4, RWLock_t8\n");
    }
    return file;
}

int main() {

    const int N = 400;

    // Number of operations
    int m = 10000;

    // Fractions for each case
    int member_frac;
    int insert_frac;
    int delete_frac;

    // Use current time as seed for random generator
    srand(time(0));

    int cases[] = {0, 1, 2};
    int fractions[][3] = {{99, 0.5, 0.5}, {90, 5, 5}, {50, 25, 25}};
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

        member_frac = fractions[i][0];
        insert_frac = fractions[i][1];
        delete_frac = fractions[i][2];

        // Perform ope;rations for the current case here

        fclose(file); // Close the file when done with it
    }
    printf("Member: %d, Insert: %d, Delete: %d\n", member_frac, insert_frac, delete_frac);

    return 0;

}


