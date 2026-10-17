#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int intVar = 0; //static variable in stack 
int main(){
  int *ptr; 
  printf("Address (ptr in heap): %p, Address (intVar in stack):  %p, value: %d\n", ptr, &intVar, intVar);
  ptr = (int *)malloc(sizeof(int)); //Heap
  if (ptr == 0) {
     printf("ERROR: Out of memory\n");
     return 1;
  }
  *ptr = intVar;
  intVar += 1;
  //sleep(1); // sleep for x seconds
  printf("Address (ptr in heap): %p, Address (intVar in stack):  %p, value: %d\n", ptr, &intVar, intVar);
  free(ptr);
  return 0;
}

