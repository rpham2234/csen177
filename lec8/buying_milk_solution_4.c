// Buying milk problem - solution try #4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// Define a structure to hold the shared data
struct d {
    bool noteA; // Note from thread A
    bool noteB; // Note from thread B
    bool milk;  // Milk status
};

// Function prototypes
void *goA(void *);
void *goB(void *);
bool buy_milk(struct d *data);

// Global variables for threads
pthread_t t1, t2;

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *)malloc(sizeof(struct d));
    data->noteA = false;
    data->noteB = false;
    data->milk = false;

    // Create threads
    pthread_create(&t1, NULL, goA, data);
    pthread_create(&t2, NULL, goB, data);

    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Free the allocated memory
    free(data);

    return 0;
}

// Thread A function
void *goA(void *arg) {
    struct d *data = arg;
    sleep(10);
    // Set noteA to true 
    data->noteA = true;

    // Check if noteB is true, if not, buy milk
    while (data->noteB) {
        ; // Do nothing, wait for noteB to become false
    }
    
    if (!data->milk) {
        printf("Thread A is buying milk\n");
        data->milk = buy_milk(data);
    }
    
    // Reset noteA
    data->noteA = false;

    // Exit the thread
    pthread_exit(0);
}

// Thread B function
void *goB(void *arg) {
    struct d *data = arg;

    // Set noteB to true
    data->noteB = true;

    // Check if noteA is false and milk is not bought, if so, buy milk
    if (!data->noteA) {
        if (!data->milk) {
            printf("Thread B is buying milk\n");
            data->milk = buy_milk(data);
        }
    }

    // Reset noteB
    data->noteB = false;

    // Exit the thread
    pthread_exit(0);
}

// Function to simulate buying milk
bool buy_milk(struct d *data) {
    return true;
}