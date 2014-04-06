all: task1 test_sat test_graph

clean: 
	rm *.o task1 test_sat test_graph

task1: task1.o sat.o transform.o graph.o
	gcc task1.o sat.o transform.o graph.o -o task1 -Wall -Wextra -g -std=c99

test_graph: test_graph.o graph.o
	gcc test_graph.o graph.o -o test_graph -Wall -Wextra -g -std=c99

test_sat: test_sat.o sat.o
	gcc test_sat.o sat.o -o test_sat -Wall -Wextra -g -std=c99

task1.o: task1.c sat.h
	gcc task1.c -c -o task1.o -Wextra -Wall -g -std=c99

test_sat.o: test_sat.c
	gcc test_sat.c -c -o test_sat.o -Wextra -Wall -g -std=c99

test_graph.o: test_graph.c
	gcc test_graph.c -c -o test_graph.o -Wextra -Wall -g -std=c99

sat.o: sat.c sat.h
	gcc sat.c -c -o sat.o -Wextra -Wall -g -std=c99

graph.o: graph.c graph.h
	gcc graph.c -c -o graph.o -Wextra -Wall -g -std=c99

transform.o: transformations.c transformations.h
	gcc transformations.c -c -o transform.o -Wextra -Wall -g -std=c99