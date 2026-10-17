// Thread Synchronization - Algorithm 2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NTHREADS 2

// Define the shared data structure
struct d {
    int j;           // Value of 'j'
    bool flag[2];    // Flags for synchronization
};

// Function prototype
void *go(void *arg);

// Array to store thread IDs
pthread_t threads[NTHREADS];

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *) malloc (sizeof(struct d));
    
    // Initialize the flags
    data -> flag[0] = false;
    data -> flag[1] = false;
    
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
    
    // Set the flag for this thread
    data -> flag[k] = true;
    
    printf("Thread %d is now attempting....\n", k);
    
    sleep(10); // Simulate some work
    
    // Busy wait until the other thread's flag is false
    while (data -> flag[!k]);
    
    printf("Thread %d is running in its Critical Section........\n", k);
    
    // Reset the flag for this thread
    data -> flag[k] = false;
    
    pthread_exit(0);
}