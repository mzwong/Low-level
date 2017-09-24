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
void* max(void *v);

/**
 * Args struct for thread function
 */
typedef struct argstruct {
    int tid;
    int *nums;
    barrier *b;
} argstruct;

int main() {
    // read in nums from stdin
    int len = 8092;
    int* nums = malloc(len * sizeof(int));
    int numCount = readNums(nums, len);

    // create threads
    int numThreads = numCount / 2;
    pthread_t tids[numThreads];
    argstruct args[numThreads];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int i;

    barrier b;
    initBarrier(&b, numThreads);
    // setup argstructs:
    for (i = 0; i < numThreads; i++) {
        args[i].tid = i;
        args[i].nums = nums;
        args[i].b = &b;
    }
    for (i = 0; i < numThreads; i++) {
        printf("here we go %d\n", i);
        pthread_create(&tids[i], &attr, max, &args[i]);
    }

    for (i = 0; i < numThreads; i++) {
        pthread_join(tids[i], NULL);
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

/**
 * Thread function to calculate the max of two numbers
 */
void* max(void *v) {
    printf("STARING HERE\n");
    int i;
    argstruct *a = (argstruct *) v;
    for (i = 0; i < 3; i++) {
        printf("YES\n");
        waitBarrier(a->b);
    }
    pthread_exit(NULL);
}
