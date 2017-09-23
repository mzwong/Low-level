/**
 * Homework 2: Parallel, binary max function
 *
 * CS4414 Operating Systems
 * Fall 2017
 *
 * Maurice Wong - mzw7af
 *
 * main.c - max function program
 *
 * COMPILE:     make
 * OBJECTS:     main.o
 * RUN:         ./max
 */

#include "barrier.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int readNums(int* nums, int len);
void createThreads(pthread_t *tids);

int main() {
    // read in nums from stdin
    int len = 8092;
    int* nums = malloc(len * sizeof(int));
    int numCount = readNums(nums, len);

    // create threads
    int numThreads = numCount / 2;
    int i;
    pthread_t tids[numThreads];
    pthread_attr attr;
    pthread_attr_init(&attr);
    for (i = 0; i < numThreads; i++) {
        pthread_create(tids)
    }
    free(nums);
    return 0;
}

/**
 * Reads in numbers from stdin into nums until newline
 * returns the # of numbers read in
 */
int readNums(int *nums, int len) {
    char line[1024];
    int numCount = 0;
    while (fgets(line, 1024, stdin)[0] != '\n') {
        if (numCount == len) {
            len *= 2;
            nums = realloc(nums, len * sizeof(int));
        }
        sscanf(line, "%d", &nums[numCount]);
        numCount++;
    }
    return numCount;
}
