/*
# Name:
# Date: <date of lab>
# Title: Lab2 - Step 5 - Four processes with individual delays
# Description: This program creates four processes, including the parent.
#              Each process iterates ten times using its own delay supplied
#              as a command-line argument.
*/

#define _DEFAULT_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    unsigned int delays[4];
    pid_t children[3];
    int child_count = 0;
    int process_index = 0;
    int fork_failed = 0;
    int i;

    if (argc != 5) {
        fprintf(stderr, "Usage: %s parent_delay child1_delay child2_delay child3_delay\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 0; i < 4; i++) {
        char *end;
        unsigned long delay;

        errno = 0;
        delay = strtoul(argv[i + 1], &end, 10);
        if (errno == ERANGE || end == argv[i + 1] || *end != '\0' ||
            delay >= 1000000UL) {
            fprintf(stderr, "Invalid delay '%s': use a number from 0 to 999999 microseconds\n",
                    argv[i + 1]);
            return EXIT_FAILURE;
        }
        delays[i] = (unsigned int)delay;
    }

    printf("\nBefore forking.\n");
    fflush(stdout);

    for (i = 1; i < 4; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            fork_failed = 1;
            break;
        }
        if (pid == 0) {
            process_index = i;
            break;
        }
        children[child_count++] = pid;
    }

    for (i = 0; i < 10; i++) {
        if (process_index == 0) {
            printf("\t\t\tI am the parent process displaying iteration %d\n", i);
        } else {
            printf("I am child process %d displaying iteration %d\n", process_index, i);
        }
        usleep(delays[process_index]);
    }

    if (process_index == 0) {
        for (i = 0; i < child_count; i++) {
            while (waitpid(children[i], NULL, 0) < 0) {
                if (errno != EINTR) {
                    perror("waitpid");
                    return EXIT_FAILURE;
                }
            }
        }
        if (fork_failed) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
