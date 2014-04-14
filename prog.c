#include "sat.h"
#include "graph.h"
#include "transformations.h"
#include <stdlib.h>

int main(){
    
	while(1){
		//declare variables used
	    int num_var;
	    colour ncol;
	    colouring cols;
	    variable *v;
	    satinstance s, new_s, reworked_s;
	    graph g;
	    //begin methods
	    printf("\nInstance: ");
	    s = read_satinstance(stdin);
	    if (s){
	    	//show in sat form
		    printf("\n%s\n","SAT form:" );
		    write_satinstance(stdout,s);
		    printf("\n");		  
		    //transform to 3SAT
		    new_s = transform_to_3sat(s);
		    //print 3SAT
		    printf("\n%s\n","Transformed to 3SAT form:" );
		    write_satinstance(stdout,new_s);
		    printf("\n");
		    //get an array of all the variables and find the total number
		    v = create_variable_array(new_s);
		    num_var = get_number_variables(v);
		    //transform to a graph
		    g = transform_to_graph(new_s, v, num_var);
		    //print out the graph
		    printf("\n%s\n\n","Transformed to Graph:");
		    write_graph(stdout,g);
		    
		    //calculate permitted colours
		    if(num_var<4){
		    	printf("Unable to use graph colouring to solve when less than 4 variables\n");

		    }else{
			    ncol = num_var+1;
			    printf("Permitted to use %i colours\n\n",ncol);
			    

			    cols = colour_graph(g,ncol);
			    //print colouring result and values that satisfy the sat expression
			    if(cols==NULL){
			    	printf("Not able to be Coloured!\n");
			    }else{
			    	print_sat_solutions(cols,s,v,num_var);
			    }
			}
		    //get from graph to sat
		    printf("\n\nExtension Task:\n");
		    printf("Reformed SAT instance:\n");
		    reworked_s = get_sat(g);
		    //print reworked sat
		    write_satinstance(stdout,reworked_s);
		    printf("\n");
		    //free memory
		    free(v);
		    destroy_satinstance_fully(new_s); 
		    destroy_satinstance_fully(s);
		    destroy_graph(g);
        }           
    }
    return 0;

}
 

