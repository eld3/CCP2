#include "sat.h"
#include <stdlib.h>
#include <ctype.h>


satinstance transform_to_3sat ( satinstance s){

	//pseudo code method

	//get number of clauses
	//for each clause
	
	//if clause length == 3
	//move on

	//if clause length < 3
	//add the clause (3-clause length times)
	//move on

	//if clause length > 3
	//panic!!

	//test each clause length


	return s;
}

//current panic plan

//length || New Clauses || Literals ||  l-3  ||
//   4   ||     1       ||    1     ||   1   ||
//   5   ||     2       ||    2     ||   2   ||
//   6   ||     3       ||    3     ||   3   ||


//if == 4
//create one new clause
//move last 2 literals to new clause
//add in new literal in first clause and its negation in the second clause.
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