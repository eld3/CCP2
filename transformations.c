#include "sat.h"
#include <stdlib.h>
#include <ctype.h>


satinstance transform_to_3sat ( satinstance s){

	//pseudo code method

	unsigned int total_clauses = number_clauses(s);
	printf("%i\n",total_clauses );
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
		//handle clauses that have more than 3 literals
		}else if (clause_length > 3){
			printf("%s\n","bigger than 3!" );
			unsigned int no_of_clauses = clause_length - 2;
			printf("This will take %i clauses\n", no_of_clauses );
			
			unsigned int curr_clause_number;
			for (curr_clause_number = 0; curr_clause_number < no_of_clauses; curr_clause_number++){

				clause curr_clause = empty_clause();

				//identify which clause is being created{}
				if (curr_clause_number == 0){
					//first clause
					printf("%s\n","First Clause");
				
				}else if (curr_clause_number == no_of_clauses - 1){
					//last clause
					printf("%s\n","Last Clause");
				
				}else{
					//middle clauses
					printf("%s\n","Middle Clause" );
				}

				
			}
			
			//create new clause
			//for clause 1 add first two existing literals
			//add new literal
			//add clause 1 to sat instance
			//add new literals negation to clause 2
	
			//startloop:

		//if curr literal is the  (clause length-1)th
			//add last two literals to current clause
			//add clause to sat instance
			//remove starting clause from sat instance
			//## end loop ##

		//else 
			//add curr literal to curr clause
			//add new literal to curr clause
			//add clause to sat instance
			//add its negation to the next clause

	//repeat loop

	//loop end:

	//move on to next clause
		}
	}
	

	
	

	//if clause length > 3
	

	return s;
}



 // void transform_to_graph ( satinstance s) {

 // }


	//if clause length == 3
	//move on to next clause

	//if clause length < 3
	//find n = number of literals(clause)
	//for 3-n
		//copy literal 1 and add to clause
	//move on to next clause

	//if clause length > 3
	//get number_lits(clause)
	//n = clause lenght - 2
	//create n new clauses

	//for clause 1 add first two existing literals
	//add new literal
	//add clause 1 to sat instance
	//add new literals negation to clause 2
	
	//startloop:

		//if curr literal is the  (clause length-1)th
			//add last two literals to current clause
			//add clause to sat instance
			//remove starting clause from sat instance
			//## end loop ##

		//else 
			//add curr literal to curr clause
			//add new literal to curr clause
			//add clause to sat instance
			//add its negation to the next clause

	//repeat loop

	//loop end:

	//move on to next clause
















//current panic plan

//length || New Clauses || Literals ||  l-3  ||
//   4   ||     1       ||    1     ||   1   ||
//   5   ||     2       ||    2     ||   2   ||
//   6   ||     3       ||    3     ||   3   ||


//if == 4
//create two new clauses
//add first two literals to the first clause
//add new literal to first clause
//add its negation to the second clause
//add last to literals to the second clause
//move on

//if == 5
//create two new clauses
//move 3rd to first new clause
//move 4th and 5th to second new clause
//add a new literal to clause 1 and its negation to clause 2
//add a new literal to clause 2 and its negation to clause 3
//move on

//if == 6
//create 3 new clauses
//move 3rd to clause 2
//move 4th to clause 3
//move 5th and 6th to clause 4
//add a new literal to clause 1 and its negation to clause 2
//add a new literal to clause 2 and its negation to clause 3
//add a new literal to clause 3 and its negation to clause 4
//move on

//if == 10
//*****BEGIN HERE******//