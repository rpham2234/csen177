/*
Name: Richard Pham
Date: October 20, 2026
Title: Lab5 – Step 3 – Producer-consumer with semaphores
Description: This program coordinates one producer thread and one consumer
thread on a shared bounded buffer. The empty and full semaphores count free
and occupied slots. A mutex semaphore gives only one thread access to the
buffer while an item is inserted or removed.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NITEMS 12

int buffer[BUFFER_SIZE];
int in_index = 0;
int out_index = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void print_buffer(const char *who, int item) {
    int i;

    printf("%s %2d | buffer: [", who, item);
    for (i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == 0)
            printf(" -");
        else
            printf(" %2d", buffer[i]);
    }
    printf(" ] in=%d out=%d\n", in_index, out_index);
}

void *producer(void *arg) {
    int item;

    (void)arg;
    for (item = 1; item <= NITEMS; item++) {
        /* remainder: create the next item outside the critical section */
        usleep(100000);

        sem_wait(&empty);   /* entry: wait for a free slot */
        sem_wait(&mutex);   /* entry: exclusive access to the buffer */

        buffer[in_index] = item;
        in_index = (in_index + 1) % BUFFER_SIZE;
        print_buffer("Produced", item);

        sem_post(&mutex);   /* exit */
        sem_post(&full);    /* exit: one more occupied slot */
    }
    return NULL;
}

void *consumer(void *arg) {
    int i;
    int item;

    (void)arg;
    for (i = 0; i < NITEMS; i++) {
        sem_wait(&full);    /* entry: wait until an item is available */
        sem_wait(&mutex);   /* entry: exclusive access to the buffer */

        item = buffer[out_index];
        buffer[out_index] = 0;
        out_index = (out_index + 1) % BUFFER_SIZE;
        print_buffer("Consumed", item);

        sem_post(&mutex);   /* exit */
        sem_post(&empty);   /* exit: one more free slot */

        /* remainder: use the item outside the critical section */
        usleep(300000);
    }
    return NULL;
}

int main(void) {
    pthread_t prod, cons;
    int i;

    for (i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    sem_init(&empty, 0, BUFFER_SIZE); /* n empty slots */
    sem_init(&full, 0, 0);            /* no items yet */
    sem_init(&mutex, 0, 1);           /* binary lock for the buffer */

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    printf("Producer and consumer finished all %d items.\n", NITEMS);
    return 0;
}
