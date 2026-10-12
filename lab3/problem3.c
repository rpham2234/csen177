/*
Name: Richard Pham
Date: October 6, 2026
Title: Lab3 - Step 3 - Send ls output through a pipe
Description: This program runs ls in a writer process and passes its output
through a pipe to a reader process, which prints the output.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// main
int main(void){
    int fds[2];
    char buff[60];
    int count;
    pipe(fds);
    if (fork()==0){
        dup2(fds[1],1);
        close(fds[0]);
        close(fds[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }
    else if(fork()==0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while((count=read(fds[0],buff,sizeof(buff)))>0){
            write(1,buff,count);
        }
        exit(0);
        }
        else{
            close(fds[0]);
            close(fds[1]);
            wait(0);
            wait(0);
        }
        return 0;
}