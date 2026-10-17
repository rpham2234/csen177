// Thread Synchronization - Swap()

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NTHREADS 2

// Function Prototype
void *go(void *arg);
void swap(bool *a, bool *b); // Function to swap two boolean values

pthread_t threads[NTHREADS];
struct d {
    int j;       // Thread identifier
    bool lock;   // Lock for synchronization
    bool key;    // Key for synchronization
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
    
    // Indicate that this thread has acquired the key
    data -> key = true;
    
    printf("Thread %d is now attempting ....\n", k);
    
    // Busy wait until the key is released
    while (data -> key)
        swap(&data -> lock, &data -> key); // Swap the values of lock and key
    
    // Simulate some work in the critical section
    printf("Thread %d is running in its Critical Section........\n", k);
    
    // Release the lock
    data -> lock = false; 
    
    pthread_exit(0);
}

// Function to swap two boolean values
void swap(bool *a, bool *b) { 
    bool temp = *a; 
    *a = *b;
    *b = temp;
}