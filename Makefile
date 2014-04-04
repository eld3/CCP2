all: task1

clean: 
	rm *.o task1

task1: task1.o
	gcc task1.o -o task1 -Wall -Wextra -g -std=c99

task1.o: task1.c task1.h
	gcc task1.c -c -o task1.o -Wextra -Wall -g -std=c99