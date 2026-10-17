/*
Name: Richard Pham
Date: October 12, 2026
Title: Lab4 – Step 2 – Fix race by passing unique index by value
Description: This program fixes the Step 1 bug by passing each thread its own
iteration index by value (cast to void*), so each thread reads a private copy
instead of racing on the shared loop variable i.
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
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i], NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    int index = (int)(size_t)arg;
    printf("Hello from thread %d with iteration %d\n",
           (int)(unsigned long)pthread_self(), index);
    pthread_exit(0);
}
