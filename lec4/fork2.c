/**************************
*	fork()
*   COEN 177
**************************/
#include <stdio.h>
#include <unistd.h>
// main
int main() {
    pid_t pid1, pid2;
    pid1 = fork(); //Two processes created
    pid2 = fork(); //Two processes created for each of the above
    if (pid1 == 0) {
        printf("\t\t Child with %d pid \n", getpid());
    }
    if (pid2 == 0) {
        printf("\tChild with %d pid \n", getpid());
    }
    printf ("Parent with %d pid \n", getpid());
return 0;
}
