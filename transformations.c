#include "sat.h"
#include <stdlib.h>
#include <ctype.h>


satinstance transform_to_3sat ( satinstance s){

	//pseudo code method


	//get number of clauses and store
	//for each clause
	
	//if clause length == 3
	//move on to next clause

	//if clause length < 3
	//add the clause (3-clause length times)
	//move on to next clause

	//if clause length > 3
	//panic!!

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
	//end loop;

	//else add curr literal to curr clause
	//add new literal to curr clause
	//add clause to sat instance
	//add its negation to the next clause

	//repeat loop

	//loop end:

	return s;
}

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