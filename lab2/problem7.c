/*
# Name:
# Date: <date of lab>
# Title: Lab2 - Step 7 - Child executes ls while parent waits
# Description: This program forks a child process that executes the ls
#              command. The parent waits until the child terminates before
#              exiting.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        execlp("/bin/ls", "ls", (char *)NULL);
        perror("execlp");
        return EXIT_FAILURE;
    }

    while (waitpid(pid, NULL, 0) < 0) {
        if (errno != EINTR) {
            perror("waitpid");
            return EXIT_FAILURE;
        }
    }

    printf("Child has completed the task!\n");
    return EXIT_SUCCESS;
}
