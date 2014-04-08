#include "sat.h"
#include "graph.h"
#include "transformations.h"
#include <stdlib.h>

int main(){
  
  
  
	while(1){
	    int num_var;
	    colour ncol;
	    colouring cols;
	    variable *v;
	    satinstance s, new_s;
	    graph g;
	    printf("\nInstance: ");
	    s = read_satinstance(stdin);
	    if (s){

		    printf("\n%s\n","SAT form:" );
		    write_satinstance(stdout,s);
		    printf("\n");
		  
		    //transform to 3SAT
		    new_s = transform_to_3sat(s);
		    //print 3SAT
		    printf("\n%s\n","Transformed to 3SAT form:" );
		    write_satinstance(stdout,new_s);
		    printf("\n");

		    //transform to graph
		    //get an array of all the variables
		    v = create_variable_array(new_s);
		    //find the size of the array - ie number of variables
		    num_var = get_number_variables(v);
		    //make a graph
		    g = transform_to_graph(new_s, v, num_var);
		    //print out graph
		    printf("\n%s\n\n","Transformed to Graph:");
		    write_graph(stdout,g);
		    ncol = num_var+1;
		    printf("Permitted to use %i colours\n\n",ncol);
		    //colour the graph
		    cols = colour_graph(g,ncol);
		    //print the truth values
		    if(cols==NULL){
		    	printf("Not able to be Coloured!\n");
		    }else{

		    	print_sat_solutions(cols,num_var,s,v);


		    }



		    //free memory
		    free(v);
		    destroy_satinstance_fully(new_s); 
		    destroy_satinstance_fully(s);
		    destroy_graph(g);
        }           
    }
    return 0;

}
 

