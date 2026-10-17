/*
Name: Richard Pham
Date: October 12, 2026
Title: Lab4 – Step 1 – Multithreaded hello with shared loop index
Description: This program creates NTHREADS threads. Each thread prints its
thread id and the loop index passed by address. Because all threads receive
a pointer to the same stack variable i, concurrent reads race with main’s
updates to i, so threads may print duplicate or unexpected iteration values.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];

int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i], NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",
    (int)(unsigned long)pthread_self(), *(int *)arg);
    pthread_exit(0);
}
