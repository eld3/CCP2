#include "sat.h"
#include <stdlib.h>
#include <ctype.h>
#include "transformations.h"


/*Task One Functions*/

/*SAT to 3SAT*//////////////////////////////////////////////////////////////////////////////////////

/*Method to transform a sat instance to 3sat*/
satinstance transform_to_3sat ( satinstance s){

	satinstance new_s = empty_satinstance();
	variable largest = largest_variable_satinstance(s);
	unsigned int total_clauses = number_clauses(s);
	//define iterator
	unsigned int i;
	for (i=0; i < total_clauses; i++){
		//get the current clause and its length
		clause curr_sat_clause = get_clause(s,i);
		unsigned int clause_length = number_lits(curr_sat_clause);
		//handle clauses that have less than 3 literals
		if (clause_length <= 3){
			//expand the clause to have three literals
			clause new_clause = expandClause(curr_sat_clause);
			add_clause(new_s,new_clause);
		//handle clauses that need to be split
		}else if (clause_length > 3){
			//split the clause in place, using a copy to preserve original sat instance
			clause copy_clause = copyClause(curr_sat_clause); //copy the clause
			largest = splitClause(new_s,copy_clause,largest);
			destroy_clause(copy_clause);			
		}
	}
	return new_s;
}


/*Helper methods for the transform_to_3SAT() method*/

/*Provides a new clause equivelent to given clause but with 3 literals*/
clause expandClause(clause curr_sat_clause){

	unsigned int j;
	//find how many literals clause missing
	unsigned int clause_length = number_lits(curr_sat_clause);
	unsigned int missing_literals = 3 - clause_length;
	clause new_clause = empty_clause();
	literal l;			
	for (j=0; j< clause_length; j++){
		//copy existing clause
		l = get_literal(curr_sat_clause,j);
		add_literal(new_clause, l);
	}
	for(j=0; j < missing_literals; j++){
		//add a new literal for every missing one
		l = get_literal(new_clause,j);
		add_literal(new_clause, l);				
	}
	return new_clause;
}


/*Returns a copy of the given clause*/
clause copyClause(clause curr_sat_clause){

	unsigned int j, clause_length;
	clause new_clause = empty_clause();
	clause_length = number_lits(curr_sat_clause);
	literal l;			
	for (j=0; j< clause_length; j++){
		//copy existing clause
		l = get_literal(curr_sat_clause,j);
		add_literal(new_clause, l);
	}
	return new_clause;
}


/*Splits the provided clause*/
int splitClause(satinstance new_s, clause copy_clause, int largest){

	int i =0;
	while(number_lits(copy_clause)>3){
		largest++; // tracks the largest
		i++; // tracks literal array pointer
		literal joiner = positive(largest);
		//make a new clause
		clause new_clause = empty_clause();				
		//add first two literals
		add_literal(new_clause,get_literal(copy_clause,0));
		add_literal(new_clause,get_literal(copy_clause,1));
		add_literal(new_clause,joiner);
		//add to sat instance
		add_clause(new_s,new_clause);
		//move lits pointer on by one
		copy_clause->lits++;
		copy_clause->length--;				
		//replace second literal with the joiner
		*(copy_clause->lits) = negative(joiner);				
		}
	clause new_copy = copyClause(copy_clause);
	add_clause(new_s,new_copy);
	//correct the copy clause pointer to free correctly
	copy_clause->lits -= i;
	return largest;
}


/*3SAT to Graph*////////////////////////////////////////////////////////////////////////////////////

/* Method to transfom a 3SAT instance to Graph*/
graph transform_to_graph ( satinstance s, variable *array, int num_var) {
	int i, j, curr_lit, num_clause, number_of_nodes;
	graph g;
	num_clause = number_clauses(s);
	//define variables to identfy that
	number_of_nodes = 3 * num_var + num_clause;
	g = empty_graph(number_of_nodes, true);	
	//join every Y to every other Y
	for ( i = FIRST_Y; i < LAST_Y; i++){
		for (j = i+1; j <= LAST_Y; j++){
			add_edge(g,i,j);
		}
	}
	//join every positive literal to its negative one
	for (i = FIRST_POS_X, j = FIRST_NEG_X; i <= LAST_POS_X; i++, j++){
		add_edge(g,i,j);
	}
	//join every Y representing a variable to all other variables apart from the one it represents
	for ( i = FIRST_Y; i <=LAST_Y; i++){
		for(j = FIRST_POS_X; j <=LAST_POS_X; j++){
			if(j != i + num_var ){
				add_edge(g,i,j);
				add_edge(g,i,j+num_var);
			}
		}
	}
	//join every Clause node to every variable not appearing in its clause
	for ( curr_lit = FIRST_POS_X; curr_lit <= LAST_NEG_X; curr_lit++){
		int curr_cl, variable_index, in_clause;
		literal l;
		variable v;
		literal clause_lit;
		//get corresponding variable
		variable_index = curr_lit % num_var;
		v = array[variable_index];
		//convert to correspondiong literal		
		if(curr_lit<FIRST_NEG_X){
			l = positive(v);
		}else{
			l= negative(v);
		}
		for(curr_cl = FIRST_CLAUSE, i = 0; curr_cl <= LAST_CLAUSE; curr_cl++, i++){
			in_clause = 0;
			clause current_clause = get_clause( s, i);
			for(j=0; j<3; j++){
				clause_lit = get_literal(current_clause,j);
				if(clause_lit==l) in_clause = 1;			
			} if(!in_clause)add_edge(g,curr_lit,curr_cl);
		}
	} return g;
}


/*Helper methods for the transform_to_graph() method*/


/*Method to create an array of variable from a SAT instance*/
variable* create_variable_array( satinstance s){
	 //define iterators
	int i, j;
	//find number of clauses 
	int num_clause = number_clauses(s);
	int max_variables = 3 * num_clause +1;
	//define array to store the variables
	variable *array = malloc(sizeof(variable)*max_variables);
	//set contents to 0
	initialise_array(array,max_variables);
	//iterate through all clauses
	int curr_arr_pos = 0;
	for (i = 0; i < num_clause; i++){		
		//iterate through every literal
 		clause c = get_clause( s, i);
		for (j = 0; j < 3; j++){
			//only add variable if it doesn't yet exist
			variable v = var(get_literal(c,j));
			if(!in_array(v,array,max_variables)){
				array[curr_arr_pos] = v;
				curr_arr_pos++;
			}
		}
 	} return array;
}


/*Method to test if element in the array*/
int in_array(variable val, variable *array, int size){

	for(int i = 0; i < size; i ++){
		if(array[i]==val){ 
			return 1;
		}
	} return 0;
}


/*Method to initialise all array elements to 0*/
void initialise_array( variable *array, int size){
	for(int i = 0; i < size; i++){
		array[i] = 0;
	}
}


/*Method to get the number of variables within an array*/
int get_number_variables( variable *array){
	//count non 0 elements
	int sum = 0;
	while(array[sum]!=0){
		++sum;
	} return sum;
}


/*Colouring to Solutions*///////////////////////////////////////////////////////////////////////////

/*Prints the solutions for the given sat instance*/
void print_sat_solutions(colouring cols, satinstance s, variable *array, int num_var){
	//declare variables
	variable v, largest_var;
	colour false_colour;
	int i, last_pos_x, node_value, value;
	//get last +ve node place
	last_pos_x = 2 * num_var -1;
	//get the false colour
	false_colour = find_false_colour(cols,num_var);
	//find the largest variable in the original sat instance
	largest_var = largest_variable_satinstance(s);
	//iterate through +ve X nodes
	for(i = num_var; i <= last_pos_x; i++){
		//find the index of the actual variable represented by the node
		node_value = i % num_var;
		v = array[node_value];
		//test if the node is false and assign result to the value
		value = (cols[i]!=false_colour);
		//print out result
		if(v<=largest_var){
			//if variable used in the sat and 3sat
			printf("Variable %i should be %i.\n",v,value);
		}else{
			//if variable used in the 3sat only
			printf("Variable %i should be %i.  (This is only present in the 3SAT form).\n",v,value);
		}
	}
}

/*Helper Methods for finding the sat expression solutions*/

/*Find the colour not used for any Y value - ie false colour*/
int find_false_colour(colouring cols, int num_var){
	for(int i = 0; i <= num_var; i++){
		if(!in_y_value(cols,i,num_var)) return i;
	} return -1;
}

/*Test if any of the Y values is coloured the given colour (c)*/
int in_y_value(colouring cols, colour c, int num_var){
	for(int i = 0; i < num_var; i++){
		if(cols[i] == c) return 1;
	} return 0;
}




/*Task 4*///////////////////////////////////////////////////////////////////////////////////////////

/*Graph to SAT*/

/*Constructs SAT from a graph note it assumes the nodes are ordered 
with Y nodes first, then +ve X then -ve X then C nodes*/
satinstance get_sat(graph g){
	//define variables
	satinstance s;
	int num_var, num_nodes, num_clause, i, j;
	literal l;
	clause c;
	//get variables
	num_var = get_variables(g);
	num_nodes = number_vertices(g);
	num_clause = num_nodes - (num_var*3);
	s = empty_satinstance();
	//create clauses
	for(i = num_var*3; i<num_nodes; i++ ){
		c = empty_clause();		
		for(j=num_var; j<=3*num_var-1; j++ ){
			if(!is_adjacent(g,i,j)){
				if(j<2*num_var){
					l = positive(j);
				}else{
					l = negative(j-num_var);
				}
				add_literal(c,l);
				if(number_lits(c)==3)break;
			}
		} add_clause(s,c);
	} return s;
}


/*Find the number of variables in a graph
works on assuming the decribed node order for 
the get_sat() method*/
int get_variables(graph g){
	//declare variables
	int i, total_nodes;
	vertex first_node;
	//set variables
	total_nodes = number_vertices(g);
	first_node = 0;
	//iterate over nodes to find first node not adjacent
	for(i=1; i<total_nodes; i++){
		//if current node adgacent to next node move on
		if(!is_adjacent(g, first_node, i)) return i;
	} return -1;
}

