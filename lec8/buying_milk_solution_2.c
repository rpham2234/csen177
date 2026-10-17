//Buying milk problem - solution try #2
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// Define a structure to hold the shared data
struct d {
    bool note;
    bool milk;
};

// Function prototypes
void *go_thread_1(void *);
void *go_thread_2(void *);
bool buy_milk(struct d *data);

// Global variables for threads and mutex
pthread_t thread_1, thread_2;

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *)malloc(sizeof(struct d));
    data->note = false;
    data->milk = false;

    // Create threads
    if (pthread_create(&thread_1, NULL, go_thread_1, data) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_2, NULL, go_thread_2, data) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Join threads
    if (pthread_join(thread_1, NULL) != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(thread_2, NULL) != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    // Free the allocated memory
    free(data);

    return 0;
}

// Thread A function
void *go_thread_1(void *arg) {
    struct d *data = arg;

    // Leave note and check if milk needs to be bought and update shared data accordingly
    data->note = true;
    if (!data->milk) {
        sleep(10);
        if (!data->note) {
            printf("Thread A is buying milk\n");
            data->milk = buy_milk(data);
            data->note = false;
        }
    }

    // Exit the thread
    pthread_exit(0);
}

// Thread B function
void *go_thread_2(void *arg) {
    struct d *data = arg;

    // Check if milk needs to be bought and update shared data accordingly
    data->note = true;
    if (!data->milk) {
        //sleep(10);
        if (!data->note) {
            printf("Thread B is buying milk\n");
            data->milk = buy_milk(data);
            data->note = false;
        }
    }

    // Exit the thread
    pthread_exit(0);
}

// Function to simulate buying milk
bool buy_milk(struct d *data) {
    return true;
}