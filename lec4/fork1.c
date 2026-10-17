/**************************
*	fork()
*   COEN 177
**************************/

#include <stdio.h>
#include <unistd.h>

//main
int main() {
	   int i;
	   printf("before forking.\n");
	   if (fork()){  // parent process
	      for (i=0;i<10;i++) {
	         printf("\t \t \t Parent  process %d \n", i );
		 sleep(1); 
	      }
	   }
	   else{ // child process
	      for (i=0;i<10;i++) {
	         printf("Child process %d  \n", i );
		 sleep(1);  
	   	  }
	   } 
  return 0;
}
