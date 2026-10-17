// Buying milk problem - solution try #1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// Define the shared data structure
struct d {
    bool note;  // Indicates if there's a note left for buying milk
    bool milk;  // Indicates if milk has been bought
};

// Function prototypes
void *goA(void *);
void *goB(void *);
bool buy_milk(struct d *data);

pthread_t t1, t2;

int main() {
    // Allocate memory for the shared data structure
    struct d *data = (struct d *) malloc (sizeof(struct d));
    
    // Initialize the data structure
    data->note = false; // Initially, no note for buying milk
    data->milk = false; // Initially, no milk bought
    
    // Create threads for A and B
    pthread_create(&t1, NULL, goA, data);
    pthread_create(&t2, NULL, goB, data);
    
    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // Free allocated memory
    free(data);
    
    return 0;
}

// Thread A function
void *goA(void *arg) {
    struct d *data = arg; 
    
    // If there's no milk and no note, thread A buys milk
    if (!data->milk){
        if (!data->note){  
            // Set the note to true to indicate that thread A is buying milk
            data->note = true;          
        
            // Print a message indicating that thread A is buying milk
            printf("Thread A is buying milk\n");
    
            // Simulate buying milk and update the milk status
            data->milk = buy_milk(data);
        
            // Reset the note after buying milk
            data->note = false;
        }
    }
    
    pthread_exit(0);
}

// Thread B function
void *goB(void *arg) {
    struct d *data = arg;
    
    // If there's no milk and no note, thread B buys milk
    if (!data->milk){ 
        if (!data->note){  
            // Set the note to true to indicate that thread B is buying milk
            data->note = true;          
        
            // Print a message indicating that thread B is buying milk
            printf("Thread B is buying milk\n");
        
            // Simulate buying milk and update the milk status
            data->milk = buy_milk(data);
        
            // Reset the note after buying milk
            data->note = false;
        }
    }
    
    pthread_exit(0);
}

// Function to simulate buying milk
bool buy_milk(struct d *data){
    return true; // Return success in buying milk
}