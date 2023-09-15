#include <sys/time.h>
#include "global.h"


// Function to calculate time spent
unsigned long time_spent(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) * 1000000 + (end->tv_usec - start->tv_usec);
}