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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int readNums(int* nums, int len);

int main() {
    int len = 8092;
    int* nums = malloc(len * sizeof(int));
    int numCount = readNums(nums, len);

    int i = 0;
    for (; i < numCount; i++) {
        printf("%d", nums[i]);
    }
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
