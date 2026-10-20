CC = gcc
CFLAGS = -Wall -pthread

all: threadSync step2 step3 step4

threadSync: threadSync.c
	$(CC) $(CFLAGS) -o threadSync threadSync.c

step2: step2.c
	$(CC) $(CFLAGS) -o step2 step2.c

step3: step3.c
	$(CC) $(CFLAGS) -o step3 step3.c

step4: step4.c
	$(CC) $(CFLAGS) -o step4 step4.c

clean:
	rm -f threadSync step2 step3 step4

.PHONY: all clean
