// Thread Synchronization - Peterson's Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NTHREADS 2

// Define the shared data structure
struct d {
    int j;           // Thread identifier
    int turn;        // Turn variable for synchronization
    bool flag[2];    // Flags for synchronization
};

// Function prototype
void *go(void *arg);

// Array to store thread IDs
pthread_t threads[NTHREADS];

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *) malloc (sizeof(struct d));
    
    // Initialize the flags and turn
    data -> flag[0] = false;
    data -> flag[1] = false;
    data -> turn = 0; // Initially, thread 0's turn
    
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
    
    // Indicate that this thread is ready to enter the critical section
    data -> flag[k] = true;
    
    // Set the turn variable to indicate the other thread's turn
    data -> turn = !k;
    
    printf("Thread %d is now attempting....\n", k);
    
    // Busy wait until it's the thread's turn and the other thread is not ready
    while (data -> flag[!k] && data -> turn == !k);
    
    // Simulate some work
    sleep(10);
    
    printf("Thread %d is running in its Critical Section........\n", k);
    
    // Reset the flag for this thread
    data -> flag[k] = false;
    
    pthread_exit(0);
}
