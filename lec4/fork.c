/**************************
*	fork()
*   COEN 177
**************************/
#include <stdio.h> 
#include <unistd.h> 

// main
int main(void) 
{ 
	int x; 
	x = 0; 
	fork(); // two processes are created
	x++; 
	printf("I am process %d and my x is %d\n", getpid(), x);
	return 0; 
}

