#ifndef BARRIER_H
#define BARRIER_H
#include <semaphore.h>

typedef struct barrier {
    int size;
    int counter;
    sem_t *waitq; // original barrier that collects threads until release
    sem_t *waitq2; // secondary barrier to hold threads until full reset
    sem_t *mutex;
} barrier;

void initBarrier(barrier b, int size);
void waitBarrier(barrier b);

#endif
