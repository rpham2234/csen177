/*
# Name:
# Date: <date of lab>
# Title: Lab2 - Step 3 - Command-line delay for parent and child processes
# Description: This program forks a child process and has the parent and child
#              iterate ten times using a delay provided as a command-line
#              argument.
*/

/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function */
/* main function with command-line arguments to pass */

int main(int argc, char *argv[]) {

    if (argc != 2) { //enforces argumentation
        printf("Please put argument in");
        exit(0);
    }

    int n;
    n = atoi(argv[1]); // n microseconds is taken as command-line argument
    pid_t pid;
    int i; // n is a delay in microseconds inserted in parent and child iterations
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