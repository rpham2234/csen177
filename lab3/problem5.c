/*
Name: Richard Pham
Date: October 6, 2026
Title: Lab3 - Step 5 - Producer-consumer communication with a pipe
Description: This program sends the numbers 1 through 10 from a producer
process to a consumer process through a pipe.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int write_all(int fd, const char *data, size_t length) {
    size_t written = 0;

    while (written < length) {
        ssize_t count = write(fd, data + written, length - written);
        if (count < 0 && errno == EINTR) {
            continue;
        }
        if (count <= 0) {
            return -1;
        }
        written += (size_t)count;
    }
    return 0;
}

int main(void) {
    int fds[2];
    pid_t consumer;

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    consumer = fork();
    if (consumer == -1) {
        perror("fork");
        close(fds[0]);
        close(fds[1]);
        return 1;
    }

    if (consumer == 0) {
        char buffer[128];
        ssize_t count;

        close(fds[1]);
        if (write_all(STDOUT_FILENO, "Consumer received: ", 19) == -1) {
            perror("write");
            close(fds[0]);
            _exit(1);
        }

        while ((count = read(fds[0], buffer, sizeof(buffer))) > 0) {
            if (write_all(STDOUT_FILENO, buffer, (size_t)count) == -1) {
                perror("write");
                close(fds[0]);
                _exit(1);
            }
        }
        if (count == -1) {
            perror("read");
            close(fds[0]);
            _exit(1);
        }

        close(fds[0]);
        _exit(0);
    }

    close(fds[0]);
    {
        char message[16];
        for (int number = 1; number <= 10; number++) {
            int length = snprintf(message, sizeof(message), "%d\n", number);
            if (length < 0 || write_all(fds[1], message, (size_t)length) == -1) {
                perror("write");
                close(fds[1]);
                waitpid(consumer, NULL, 0);
                return 1;
            }
        }
    }
    close(fds[1]);

    if (waitpid(consumer, NULL, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    return 0;
}