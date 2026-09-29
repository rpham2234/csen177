/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
/*
# Name:
# Date: <date of lab>
# Title: Lab2 - Step 1 - Child executes ls; parent waits for completion
# Description: This program forks a child process that executes the ls command.
#              The parent waits until the child terminates, then prints a
#              completion message.
*/

#include <errno.h> /* errno */
/* main function */
int main() {
    pid_t pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid){
    // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
            usleep(n);
        }
        wait();
    }
    else{
    // Child process: pid = 0
        for (i=0;i<10;i++) {
        printf("I am the child process displaying iteration %d\n",i);
        usleep(n);
        }
    }
    return 0;
}