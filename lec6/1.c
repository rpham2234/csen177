#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
int main(){
  if (fork()) {
	wait(0);
	printf("Print 1\n");
  } else {
	printf("Print 2\n");
	exit(0); 
  } 
  return 0;
} 
