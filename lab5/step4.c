/*
Name: Richard Pham
Date: October 20, 2026
Title: Lab5 – Step 4 – Producer-consumer with a mutex and condition variables
Description: This program coordinates one producer thread and one consumer
thread on a shared bounded buffer. A mutex protects the buffer. Condition
variables empty and full let a thread sleep when the buffer is full or empty
instead of spinning. The waiter releases the mutex while it sleeps, and the
other thread signals it when the waited-for condition becomes true.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NITEMS 12

int buffer[BUFFER_SIZE];
int in_index = 0;
int out_index = 0;
int count = 0; /* number of items currently in the buffer */

pthread_mutex_t mutex;
pthread_cond_t empty; /* signaled when a free slot appears */
pthread_cond_t full;  /* signaled when an item is added */

void print_buffer(const char *who, int item) {
    int i;

    printf("%s %2d | buffer: [", who, item);
    for (i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == 0)
            printf(" -");
        else
            printf(" %2d", buffer[i]);
    }
    printf(" ] in=%d out=%d count=%d\n", in_index, out_index, count);
}

void *producer(void *arg) {
    int item;

    (void)arg;
    for (item = 1; item <= NITEMS; item++) {
        usleep(100000);

        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE)          /* buffer is full */
            pthread_cond_wait(&empty, &mutex);

        buffer[in_index] = item;
        in_index = (in_index + 1) % BUFFER_SIZE;
        count++;
        print_buffer("Produced", item);

        pthread_cond_signal(&full);           /* an item is available */
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    int i;
    int item;

    (void)arg;
    for (i = 0; i < NITEMS; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0)                    /* buffer is empty */
            pthread_cond_wait(&full, &mutex);

        item = buffer[out_index];
        buffer[out_index] = 0;
        out_index = (out_index + 1) % BUFFER_SIZE;
        count--;
        print_buffer("Consumed", item);

        pthread_cond_signal(&empty);          /* a free slot is available */
        pthread_mutex_unlock(&mutex);

        usleep(300000);
    }
    return NULL;
}

int main(void) {
    pthread_t prod, cons;
    int i;

    for (i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    pthread_mutex_destroy(&mutex);
    printf("Producer and consumer finished all %d items.\n", NITEMS);
    return 0;
}
