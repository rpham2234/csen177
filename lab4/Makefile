CC = gcc
CFLAGS = -Wall -pthread

all: step1 step2 step3 step4

step1: step1.c
	$(CC) $(CFLAGS) -o step1 step1.c

step2: step2.c
	$(CC) $(CFLAGS) -o step2 step2.c

step3: step3.c
	$(CC) $(CFLAGS) -o step3 step3.c

step4: step4.c
	$(CC) $(CFLAGS) -o step4 step4.c

clean:
	rm -f step1 step2 step3 step4

.PHONY: all clean
