/*
Name: Richard Pham
Date: October 6, 2026
Title: Lab3 - Step 6 - Producer-consumer communication with shared memory
Description: This program sends the numbers 1 through 10 from a producer
process to a consumer process using shared memory and semaphores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct shared_message {
    int value;
};

int main(void) {
    int shmid = shmget(IPC_PRIVATE, sizeof(struct shared_message), IPC_CREAT | 0600);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    struct shared_message *shared = shmat(shmid, NULL, 0);
    if (shared == (void *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    int semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600);
    if (semid == -1) {
        perror("semget");
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    unsigned short initial_values[] = {1, 0};
    union semun sem_values;
    sem_values.array = initial_values;
    if (semctl(semid, 0, SETALL, sem_values) == -1) {
        perror("semctl SETALL");
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    pid_t consumer = fork();
    if (consumer == -1) {
        perror("fork");
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    if (consumer == 0) {
        for (int number = 1; number <= 10; number++) {
            struct sembuf wait_for_message = {1, -1, 0};
            if (semop(semid, &wait_for_message, 1) == -1) {
                perror("semop consumer wait");
                shmdt(shared);
                _exit(1);
            }
            printf("Consumer received: %d\n", shared->value);
            fflush(stdout);

            struct sembuf release_buffer = {0, 1, 0};
            if (semop(semid, &release_buffer, 1) == -1) {
                perror("semop consumer release");
                shmdt(shared);
                _exit(1);
            }
        }
        shmdt(shared);
        _exit(0);
    }

    for (int number = 1; number <= 10; number++) {
        struct sembuf wait_for_empty = {0, -1, 0};
        if (semop(semid, &wait_for_empty, 1) == -1) {
            perror("semop producer wait");
            waitpid(consumer, NULL, 0);
            shmdt(shared);
            shmctl(shmid, IPC_RMID, NULL);
            semctl(semid, 0, IPC_RMID);
            return 1;
        }

        shared->value = number;
        struct sembuf signal_message = {1, 1, 0};
        if (semop(semid, &signal_message, 1) == -1) {
            perror("semop producer signal");
            waitpid(consumer, NULL, 0);
            shmdt(shared);
            shmctl(shmid, IPC_RMID, NULL);
            semctl(semid, 0, IPC_RMID);
            return 1;
        }
    }

    int status;
    if (waitpid(consumer, &status, 0) == -1) {
        perror("waitpid");
        status = 1;
    }

    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return status == 0 ? 0 : 1;
}