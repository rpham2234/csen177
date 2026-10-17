// Thread Synchronization - n processes

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h> 

#define N 5 // Nthreads

pthread_t thread_id[N];
int flag[N], turn[N];

// Function to leave the critical section
void leaveCS(int i) {
    flag[i] = -1; // Set flag to -1 to indicate the thread is no longer in or wants the CS.
    printf("Thread %d left Critical Section\n", i);
}

// Function to enter the critical section
void enterCS(int i) {
    // The thread must pass through N-1 levels to enter the critical section.
    for (int level = 0; level < N - 1; level++) {
        flag[i] = level;
        turn[level] = i;
        int other_thread_ahead = 1;
        while (other_thread_ahead && turn[level] == i) {
            other_thread_ahead = 0; // Reset for re-check
            for (int j = 0; j < N; j++) {
                if (i == j) continue; // Don't check against self
                if (flag[j] >= level) {
                    other_thread_ahead = 1; // Found a competing thread
                    break;
                }
            }
        }
    }
    printf("Thread %d entered Critical Section\n", i);
}

// Thread function
void *thread(void* arg) {
    intptr_t i = (intptr_t)arg; // Cast pointer to intptr_t
    enterCS(i); // Enter critical section
    sleep(1); // Simulate some work
    leaveCS(i); // Leave critical section
    printf("Goodbye\n");
    pthread_exit(0);
}

int main() {
    int i;
    for (i = 0; i < N; i++) {
        flag[i] = -1;
    }
    // Create threads
    for (i = 0; i < N; i++)
        pthread_create(&thread_id[i], NULL, thread, (void*)(size_t)i);

    // Wait for threads to finish
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}

