#include "sat.h"
#include <stdlib.h>
#include <ctype.h>
#include "transformations.h"


/*This methods gets an instance of SAT from a given graph
it assumes the nodes are ordered with Y nodes first, then
+ve X then -ve X then C nodes*/
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
		}
		add_clause(s,c);
	}	
	return s;
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
		if(!is_adjacent(g, first_node, i)) return i;//if current node adgacent to next node move on
	}
	return -1;
}

/*Prints the solutions for the given sat instance*/
void print_sat_solutions(colouring cols, int num_var, satinstance s, variable *array){
	//declare variables
	variable v, largest_var;
	colour false_colour;
	int i, last_pos_literal, node_value, value;
	//get last +ve node place
	last_pos_literal = 2 * num_var -1;
	//get the false colour
	false_colour = find_false_colour(cols,num_var);
	//find the largest variable in the original sat instance
	largest_var = largest_variable_satinstance(s);
	//iterate through +ve X nodes
	for(i = num_var; i <= last_pos_literal; i++){
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

/*Find the colour not used for any Y value - ie false colour*/
int find_false_colour(colouring cols, int num_var){
	for(int i = 0; i <= num_var; i++){
		if(!in_y_value(cols,i,num_var)) return i;
	}return -1;
}

/*Test if any of the Y values is coloured the given colour (c)*/
int in_y_value(colouring cols, colour c, int num_var){
	for(int i = 0; i < num_var; i++){
		if(cols[i] == c) return 1;
	} return 0;
}




/* Method to transfom a 3SAT instance to Graph*/
graph transform_to_graph ( satinstance s, variable *array, int num_var) {
	//define iterators
	int i, j, curr_lit;
	int num_clause = number_clauses(s);
	printf("Number of variables at transform start %i\n",num_var );
	//define variables to identfy that
	int number_of_nodes = 3 * num_var + num_clause;
	//markers for node positioning
	int first_Y = 0;
	int last_Y = num_var-1;
	int first_pos_literal = num_var;
	int last_pos_literal = 2 * num_var -1;
	int first_neg_literal = 2 * num_var;
	int last_neg_literal = 3 * num_var -1;
	int first_clause = 3 * num_var;
	int last_clause = number_of_nodes -1;
	//create graph
	graph g = empty_graph(number_of_nodes, true);	
	//join every Y to every other Y
	for ( i = first_Y; i < last_Y; i++){
		for (j = i+1; j <= last_Y; j++){
			//link all Y's
			add_edge(g,i,j);
		}
	}
	//join every positive literal to its negative one
	for (i = first_pos_literal, j = first_neg_literal; i <= last_pos_literal; i++, j++){
		add_edge(g,i,j);
	}
	//join every Y representing a variable to all other variables apart from the one it represents
	for ( i = first_Y; i <=last_Y; i++){
		//positive literals
		for(j = first_pos_literal; j <=last_pos_literal; j++){
			if(j != i + num_var ){
				add_edge(g,i,j);
				add_edge(g,i,j+num_var);
			}
		}
	}
	//join every Clause node to every variable not appearing in its clause
	for ( curr_lit = first_pos_literal; curr_lit <= last_neg_literal; curr_lit++){
		int curr_cl, variable_index, in_clause;
		literal l;
		variable v;
		literal clause_lit;
		//get corresponding variable
		variable_index = curr_lit % num_var;
		v = array[variable_index];
		//convert to correspondiong literal		
		if(curr_lit<first_neg_literal){
			l = positive(v);
		}else{
			l= negative(v);
		}
		for(curr_cl = first_clause, i = 0; curr_cl <= last_clause; curr_cl++, i++){
			in_clause = 0;
			clause current_clause = get_clause( s, i);
			for(j=0; j<3; j++){
				clause_lit = get_literal(current_clause,j);
				if(clause_lit==l){
					in_clause = 1;
				}			
			}
			if(!in_clause)add_edge(g,curr_lit,curr_cl);
		}
	}
	return g;
}


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
 	}
 	return array;
}

/*Method to test if element in the array*/
int in_array(variable val, variable *array, int size){

	for(int i = 0; i < size; i ++){
		if(array[i]==val){ 
			return 1;
		}
	}
	return 0;
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
	}
	return sum;
}

/*Method to transform a sat instance to 3sat*/
satinstance transform_to_3sat ( satinstance s){

	//pseudo code method
	satinstance new_s = empty_satinstance();
	variable largest = largest_variable_satinstance(s);
	unsigned int total_clauses = number_clauses(s);
	//define iterator
	unsigned int i, j;
	for (i=0; i < total_clauses; i++){
		//get the current clause and its length
		clause curr_sat_clause = get_clause(s,i);
		unsigned int clause_length = number_lits(curr_sat_clause);
		//handle clauses that have less than 3 literals
		if (clause_length <= 3){
			//find how many literals clause missing
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
			add_clause(new_s,new_clause);
		}else if (clause_length > 3){
			unsigned int no_of_clauses = clause_length - 2;
			clause curr_clause;
			variable clause_joiner;
			int current_sat_literal = 0;			
			unsigned int curr_clause_number;
			for (curr_clause_number = 0; curr_clause_number < no_of_clauses; curr_clause_number++){
				curr_clause = empty_clause();				
				//identify which clause is being created{}
				if (curr_clause_number == 0){
					//first clause
					//for clause 1 add first two existing literals
					literal first = get_literal(curr_sat_clause,current_sat_literal);
					current_sat_literal++;
					add_literal(curr_clause,first);	
					//add second literal				
					literal second = get_literal(curr_sat_clause,current_sat_literal);
					current_sat_literal++;
					add_literal(curr_clause,second);
					//create a variable bigger than current largest
					largest++;
					clause_joiner = largest;
					//add its positive version to the clause
					literal lit_to_add = positive(clause_joiner);
					add_literal(curr_clause,lit_to_add);
					//add the whole clause to the sat instance
					add_clause(new_s,curr_clause);				
				}else if (curr_clause_number == no_of_clauses - 1){
					//last clause
					//add negation from previously added new literal to curr clause
					literal lit_to_add = negative(clause_joiner);
					add_literal(curr_clause,lit_to_add);
					//add last two literals to current clause
					lit_to_add = get_literal(curr_sat_clause,current_sat_literal);
					current_sat_literal++;
					add_literal(curr_clause, lit_to_add);
					lit_to_add = get_literal(curr_sat_clause,current_sat_literal);
					current_sat_literal++;
					add_literal(curr_clause, lit_to_add);
					//add the whole clause to the sat instance
					add_clause(new_s,curr_clause);
					//remove starting clause from sat instance				
				}else{
					//middle clauses
					//add negation from previously added new literal to curr clause
					literal lit_to_add = negative(clause_joiner);
					add_literal(curr_clause,lit_to_add);
					//add the next original literal
					lit_to_add = get_literal(curr_sat_clause,current_sat_literal);
					current_sat_literal++;
					add_literal(curr_clause, lit_to_add);
					largest++;
					clause_joiner = largest;
					//add its positive version to the clause
					lit_to_add = positive(clause_joiner);
					add_literal(curr_clause,lit_to_add);
					//add the whole clause to the sat instance
					add_clause(new_s,curr_clause);
				}	
			}			
		}
	}
	return new_s;
}
