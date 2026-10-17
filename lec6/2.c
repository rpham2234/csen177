//2.c
#include <stdio.h>
#include <unistd.h>
int x = 1;
int main() {
  if (!fork()) //parent (x=1), child (x=1)
	  x++;       //child (x=2)
  else if (!fork()) //parent (x=1), new child (x=1)
 	  x += 2;  //new child (x=3)
  printf("%d\n",x);
  return 0;
}

