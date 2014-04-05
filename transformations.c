#include "sat.h"
#include <stdlib.h>
#include <ctype.h>


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



 // void transform_to_graph ( satinstance s) {

 // }

