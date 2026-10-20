/*
Name: Richard Pham
Date: October 20, 2026
Title: Lab5 – Step 2 – Thread synchronization with a mutex lock
Description: This program is the Step 1 example rewritten with a pthread mutex
instead of a semaphore. Ten threads each lock the mutex before the critical
section and unlock it afterward, so only one thread runs in that section at
a time.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NTHREADS 10

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

int main(void) {
    int i;

    signal(SIGINT, cleanup);
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n", (int)(size_t)arg);
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n", (int)(size_t)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void cleanup(int sigtype) {
    (void)sigtype;
    printf("\n Terminating\n");
    exit(0);
}
