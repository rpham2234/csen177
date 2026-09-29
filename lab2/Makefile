all: problem1.c problem3.c problem5.c problem7.c
	gcc -o problem1 problem1.c
	gcc -o problem3 problem3.c
	gcc -o problem5 problem5.c
	gcc -o problem7 problem7.c -lpthread

one: problem1.c
	gcc -o problem1 problem1.c

two: problem3.c
	gcc -o problem3 problem3.c

three: problem5.c
	gcc -o problem5 problem5.c

four: problem7.c
	gcc -o problem7 problem7.c -lpthread

clean:; rm -f problem1 problem3 problem5 problem7
