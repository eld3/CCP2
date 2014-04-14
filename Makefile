all: prog 

clean: 
	rm *.o prog 

prog: prog.o sat.o transform.o graph.o
	gcc prog.o sat.o transform.o graph.o -o prog -Wall -Wextra -g -std=c99

prog.o: prog.c sat.h
	gcc prog.c -c -o prog.o -Wextra -Wall -g -std=c99

transform.o: transformations.c transformations.h
	gcc transformations.c -c -o transform.o -Wextra -Wall -g -std=c99

sat.o: sat.c sat.h
	gcc sat.c -c -o sat.o -Wextra -Wall -g -std=c99

graph.o: graph.c graph.h
	gcc graph.c -c -o graph.o -Wextra -Wall -g -std=c99

