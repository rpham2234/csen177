/*
Name: Richard Pham
Date: October 6, 2026
Title: Lab3 - Step 1 - Pipe ls -l output to more
Description: This program creates a pipe, runs ls -l in one child process,
and passes its output to more in another child process.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 redirects stdin to downstream of pipe */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", (char *)NULL);
    }
    /*child 2 redirects stdout to upstream of pipe */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", "-l", (char *)NULL);
    }
    else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }   
    return 0;
}