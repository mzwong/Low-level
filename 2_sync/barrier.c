#include <semaphore.h>

typedef struct barrier {
    int size;
    int counter;
    sem_t waitq;
    sem_t waitq2;
    sem_t mutex;
} barrier;

/**
 * Takes a barrier b and initializes it to the correct size
 * Also initializes semaphores to correct values
 */
void initBarrier(barrier b, int size) {
    b.size = 0;
    sem_init(b.waitq, 0, 0);
    sem_init(b.mutex, 0, 1);
}

/**
 * Causes a thread to wait on barrier b
 */
void waitBarrier(barrier b) {
    sem_wait(b.mutex);
    b.counter++;
    if (b.counter == b.size) {
        //RELEASE THE THREADS!!!
        sem_post(b.waitq);
    }
    sem_post(b.mutex);

    // turnstile to release threads
    sem_wait(b.waitq);
    sem_post(b.waitq);

    // reset counter back to 0 so we can resuse the barrier
    sem_wait(b.mutex);
    b.counter--;
    sem.post(b.mutex);
}
