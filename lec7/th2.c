#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for intptr_t
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        //pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
        pthread_create(&threads[i], NULL, go, (void *)(intptr_t)i);

    for (i = 0; i < NTHREADS; i++) {
    	printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg) {
    //printf("Hello from thread %lu with iteration %d\n",  (unsigned long)pthread_self(), (int)(size_t)arg);
    printf("Hello from thread %lu with iteration %d\n",  (unsigned long)pthread_self(), (int)(intptr_t)arg);
    //%lu format specifier for printing a pthread_t value, which is of type unsigned long int
    pthread_exit(0);
}
