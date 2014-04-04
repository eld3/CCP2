all: task1 test_sat

clean: 
	rm *.o task1 test_sat

task1: task1.o sat.o transform.o
	gcc task1.o sat.o -o task1 -Wall -Wextra -g -std=c99

task1.o: task1.c sat.h
	gcc task1.c -c -o task1.o -Wextra -Wall -g -std=c99

test_sat: test_sat.o sat.o
	gcc test_sat.o sat.o -o test_sat -Wall -Wextra -g -std=c99

test_sat.o: test_sat.c
	gcc test_sat.c -c -o test_sat.o -Wextra -Wall -g -std=c99

sat.o: sat.c sat.h
	gcc sat.c -c -o sat.o -Wextra -Wall -g -std=c99

transform.o: transformations.c sat.h
	gcc transformations.c -c -o transform.o -Wextra -Wall -g -std=c99