/*
Name: Richard Pham
Date: October 6, 2026
Title: Lab3 - Step 4 - Filter passwd entries with grep
Description: This program pipes the output of cat /etc/passwd to grep root
and prints lines containing root.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fds[2];
    pid_t cat_pid;
    pid_t grep_pid;

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    cat_pid = fork();
    if (cat_pid == 0) {
        if (dup2(fds[1], STDOUT_FILENO) == -1) {
            perror("dup2 cat");
            exit(1);
        }
        close(fds[0]);
        close(fds[1]);
        execlp("cat", "cat", "/etc/passwd", (char *)NULL);
        perror("execlp cat");
        exit(1);
    }
    if (cat_pid == -1) {
        perror("fork cat");
        close(fds[0]);
        close(fds[1]);
        return 1;
    }

    grep_pid = fork();
    if (grep_pid == 0) {
        if (dup2(fds[0], STDIN_FILENO) == -1) {
            perror("dup2 grep");
            exit(1);
        }
        close(fds[0]);
        close(fds[1]);
        execlp("grep", "grep", "root", (char *)NULL);
        perror("execlp grep");
        exit(1);
    }
    if (grep_pid == -1) {
        perror("fork grep");
        close(fds[0]);
        close(fds[1]);
        waitpid(cat_pid, NULL, 0);
        return 1;
    }

    close(fds[0]);
    close(fds[1]);
    waitpid(cat_pid, NULL, 0);
    waitpid(grep_pid, NULL, 0);
    return 0;
}