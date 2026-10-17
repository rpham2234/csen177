//threads
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int x = 1;
void* thread1(void* arg) {
    x++;                
    pthread_exit(0);
}
void* thread2(void* arg) {
    x += 2;            
    pthread_exit(0);
}
int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL); //simulate child
    pthread_create(&t2, NULL, thread2, NULL); //simulate new child
    pthread_join(t1, NULL); //wait for child to finish
    pthread_join(t2, NULL); //wait for new child to finish
    printf("%d\n", x);
    return 0;
}

mov eax, DWORD PTR [x]   ; Load x into register eax
add eax, 1               ; Increment the value in eax
mov DWORD PTR [x], eax   ; Store it back to x
