// Thread Synchronization - TestAndSet()

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NTHREADS 2

// Function Prototype
void *go(void *arg);
bool TestAndSet(bool *value); // Function to perform TestAndSet operation

pthread_t threads[NTHREADS];
struct d {
    int j;       // Thread identifier
    bool lock;   // Lock for synchronization
};

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *) malloc (sizeof(struct d));
    
    // Initialize the lock
    data -> lock = false;
    
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
    
    printf("Thread %d is now attempting ....\n", k);
    
    // Spin until the lock is acquired using TestAndSet
    while (TestAndSet(&data -> lock));
    
    printf("T %d Lock %d....\n", k, data -> lock);
    // Simulate some work in the critical section
    printf("Thread %d is running in its Critical Section........\n", k);
    
    // Release the lock
    data -> lock = false; 
    printf("T %d Lock %d....\n", k, data -> lock);
    
    pthread_exit(0);
}

// Function to perform TestAndSet operation
bool TestAndSet(bool *value) { 
    bool temp = *value;
    *value = true; 
    return temp;
}