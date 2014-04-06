#include "sat.h"
#include <stdlib.h>
#include <ctype.h>
#include "transformations.h"



   graph transform_to_graph ( satinstance s) {
   	//define iterators
	int i, j, k;
	//find number of clauses 
	int num_clause = number_clauses(s);
	//maximum variables
	int max_variables = 3 * num_clause;
	//define array to store the variables
	variable array[max_variables];
	initialise_array(array,max_variables);
	//iterate through all clauses
	int curr_arr_pos = 0;
	for (i = 0; i < num_clause; i++){		
	//iterate through every literal]
	 	clause c = get_clause( s, i);
		for (j = 0; j < 3; j++){
			variable v = var(get_literal(c,j));
			if(!in_array(v,array,max_variables)){
				printf("Not in array, clause %i, %i\n",i,j);
				array[curr_arr_pos] = v;
				curr_arr_pos++;
			}
		}
	 }
	 int number_variables = curr_arr_pos;
	
	
	//define variables to identfy that
	int number_of_nodes = 3 * number_variables + num_clause;
	printf("%s%i\n","number of variables ", number_variables );
	//markers for node positioning
	int first_Y = 0;
	int last_Y = number_variables-1;
	int first_pos_literal = number_variables;
	int last_pos_literal = 2 * number_variables -1;
	int first_neg_literal = 2 * number_variables;
	int last_neg_literal = 3 * number_variables -1;
	int first_clause = 3 * number_variables;
	int last_clause = number_of_nodes -1;
	
	//calculate number of nodes needed
	
	//3*sum of variables + number of clauses
	
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

	for ( i = first_Y; i < last_Y; i++){
		for(j = first_pos_literal; j < last_pos_literal; j++){
			if(j != i + number_variables ){
				add_edge(g,i,j);
			}
		}
		 for(k = first_neg_literal; k < last_neg_literal; k++){
			if(k != i + 2* number_variables ){
				add_edge(g,i,k);
			}
		 }
	}

	//join every Clause node to every variable not appearing in its clause

	//save n somewhere your gonna need it when colouring?!
   	return g;
   }



int in_array(variable val, variable *array, int size){

	int i;
	for( i = 0; i < size; i ++){
		if(array[i]==val){ 
			printf("Match\n");
			return 1;
		}
	}
	return 0;
}

void initialise_array( variable *array, int size){

	int i;
	for( i = 0; i < size; i++){
		array[i] = 0;
	}
}




satinstance transform_to_3sat ( satinstance s){

	//pseudo code method
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
		if (clause_length < 3){
			//find how many literals clause missing
			unsigned int missing_literals = 3 - clause_length;
			//define iterator
			unsigned int j;
			for(j=0; j<missing_literals; j++){
				//add a new literal for every missing one
				literal l = get_literal(curr_sat_clause,j);
				add_literal(curr_sat_clause, l);				
			}
			add_clause(new_s,curr_sat_clause);
		//handle clauses that have more than 3 literals
		}else if(clause_length == 3){
			add_clause(new_s,curr_sat_clause);

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
	destroy_satinstance(s);
	return new_s;
}



//pseudo code for the graph transformation
	//take your 3 sat form
	//get total number of variables
	//get total number of clauses
	
	//add a node to represent every variable (Y's)
	//add a node to represent every +ve literal
	//add a node to represent every -ve literal
	//add a node to represent every clause
	
	//join every positive literal to its negative one
	//join every Y to every other Y
	//join every Y representing a variable to all other variables than the one it represents
	//join every Clause node to every variable not appearing in its clause

	//return the new graph
