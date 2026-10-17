// Thread Synchronization - Algorithm 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NTHREADS 2

// Define the shared data structure
struct d {
    int j;     // Value of 'j'
    int turn;  // Turn variable for synchronization
};

// Function prototype
void *go(void *arg);

// Array to store thread IDs
pthread_t threads[NTHREADS];

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *) malloc (sizeof(struct d));
    
    // Initialize the turn variable
    data -> turn = 0;
    
    int i;
    // Create threads
    for (i = 0; i < NTHREADS; i++){
        data -> j = i;  
        pthread_create(&threads[i], NULL, go, data);
        sleep(1); // Sleep to stagger thread creation
    }
    
    // Join threads
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i], NULL);
    
    // Free allocated memory
    free(data);
    
    return 0;
}

// Thread function
void *go(void *arg) {
    struct d *data = arg;
    int k = data -> j; // Get the value of 'j'
    
    if (k == 0)
        sleep(1000); // Sleep for thread 0 to simulate a long operation
    
    printf("Thread %d is now attempting....\n", k);
    
    // Busy wait until it's the thread's turn
    while (data -> turn != k);
    
    printf("Thread %d is running in its Critical Section........\n", k);
    
    // Change the turn variable to the next thread
    data -> turn = !k;
    
    pthread_exit(0);
}
