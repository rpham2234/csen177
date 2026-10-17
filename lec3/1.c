#include <stdio.h>
#include <unistd.h>
int intVar = 0; 
int main(){
  intVar += 1;
  sleep(1); // sleep for x seconds
  printf("Address: %p, value: %d\n", &intVar, intVar);
  return 0;
}

