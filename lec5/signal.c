#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void cleanup(int sigtype){
   printf("\n Terminating\n");
   //exit(0);
}

int main(){
	int count;
	signal(SIGINT,cleanup);
	printf("Press Ctrl-C to terminate\n");
	for(;;);
 return 0; 
}

