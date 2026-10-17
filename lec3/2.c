#include <stdio.h>
#include <unistd.h>
//2.c
void printing(int *ptr, int var);

int intVar = 0; 
int main(){
  intVar += 1;
  sleep(1); // sleep for x seconds
  printing(&intVar, intVar);
  printing(&intVar, intVar);
  return 0;
}

void printing(int *ptr, int var){
  printf("Address: %p, value: %d\n", ptr, var);
}
