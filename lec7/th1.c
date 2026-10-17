//Thread 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10

pthread_t threads[NTHREADS]; //array of threads arguments

int main() {
	int i;
	for (i = 0; i < NTHREADS; i++)
		pthread_create(&threads[i], NULL, go, &i); //passing address of i not actual value

	for (i = 0; i < NTHREADS; i++) {
		printf("Thread %d returned\n", i);
		pthread_join(threads[i],NULL);
	}
	printf("Main thread done.\n");
	return 0;
}

//thread go function
void *go(void *arg) {
	printf("Hello from thread %lu with iteration %d\n", (unsigned long)pthread_self(), *(int *)arg );
//%lu format specifier for printing a pthread_t value, which is of type unsigned long int
	pthread_exit(0);
}

