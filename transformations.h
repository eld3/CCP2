#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


#include <stdio.h>
#include "sat.h"
#include "graph.h"

//Definitions used in 3sat to graph transformation

#define FIRST_Y 0
#define LAST_Y num_var-1
#define FIRST_POS_X num_var
#define LAST_POS_X 2*num_var-1
#define FIRST_NEG_X 2*num_var
#define LAST_NEG_X 3*num_var-1
#define FIRST_CLAUSE 3*num_var
#define LAST_CLAUSE number_of_nodes-1


/*Task 1 Core Functions*////////////////////////////////////////////////////////////////////////////

/*Function takes a given sat instance and returns a new sat instance in strict 3SAT compliant form
this means every clause has exactly 3 literals*/
extern satinstance transform_to_3sat ( satinstance s);

/*Given an sat instance, and array of its variables and the sixe of the array produces a graph, with
order Y nodes, X+ nodes, X- nodes and clause nodes. Colouring this graph with n+1 colours 
succesfully will determine values that satisfy the sat*/
extern graph transform_to_graph ( satinstance s, variable *v, int num_var);

/*Given a graph colouring the corresponding sat instance an array of variables in the sat instance 
and its size, finds and prints values satisfying the sat instance*/
extern void print_sat_solutions( colouring cols, satinstance s, variable *array, int num_var );


/* Task 1 Helper Functions *//////////////////////////////////////////

/*transform_to_3sat helper functions*/////////////////////////////////

/*Given a clause with 3 or less literals creates a new clause. Ensures 
a clause has 3 literals, expand the clause to an equivelent 
expression if less than 3, if already 3 simply copies the clause*/
extern clause expandClause(clause c);

/*Given a copy of a clause with >3 literals, constructs 3 literal clauses to represent the clause
and adds them to the provided sat instance, new variables used will be higer than the largest
provided and it returns the highest new variable added, sop the new largest can be updated*/
extern int splitClause(satinstance new_s, clause copy_clause, int largest);

/*Given a clause returns a copy of the clause*/
extern clause copyClause(clause c);


/*Transform to graph helper functions*////////////////////////////////

/*Checks if a cariable provided is within the given array, must also provide array size*/
extern int in_array(variable val, variable *array, int size);

/*Given an array and its size initialises each element to 0*/
extern void initialise_array( variable *array, int size);

/*Given an array of variables returns the number of elements ie size*/
extern int get_number_variables( variable *array);

/*Given a sat instance creates an array of all variables appearing ignoring duplicates*/
extern variable* create_variable_array(satinstance s);


/*Find sat solutions helper methods*//////////////////////////////////

/*Checks if the colour given is used for any of the Y nodes, ie node 0 to num_var*/
extern int in_y_value(colouring cols, colour c, int num_var);

/*Finds the one colour not used in the Y nodes, should in theory
always be n + 1, but ignores this to allow use with a different
colouring algorithm*/
extern int find_false_colour(colouring cols, int num_var);


/*Task 4 functions*/////////////////////////////////////////////////////////////////////////////////

/*Given a graph, with node order Y nodes, X+ nodes, X- nodes and Clause nodes reconstructs a sat
representation, will not incluided any duplicates, will not work for a graph constructed with a 
different node order*/
extern satinstance get_sat(graph g);

/*Given a graph in order Y node, X+ nodes, X-ve nodes and Clause nodes, fidn the number of variables
by identifying the distance between the first node and the first X+ node*/
extern int get_variables(graph g);


#endif