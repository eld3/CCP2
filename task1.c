#include "sat.h"
#include "graph.h"
#include "transformations.h"

main()
{
  satinstance s;
  while(1)
    {
      printf("Instance: ");
      s = read_satinstance(stdin);
      if (s)
	{
	  printf("\n%s\n","SAT form:" );
	  write_satinstance(stdout,s);
	  printf("\n");
	  
	  //transform to 3SAT
	  s = transform_to_3sat(s);
	  //print 3SAT
	  printf("\n%s\n","Transformed to 3SAT form:" );
	  write_satinstance(stdout,s);
	  printf("\n");

	  //transform to graph
	  //get an array of all the variables
	  variable *v = create_variable_array(s);
	  //find the size of the array - ie number of variables
	  int num_var = get_size(v);
	  //make a graph
	  graph g = transform_to_graph(s, v, num_var);
	  //print out graph
	  printf("\n%s\n","Transformed to Graph:");
	  write_graph(stdout,g);
	  printf("Permitted to use %i colours\n",num_var+1);


	  //write_satinstance(stdout,s);
	  //printf("\n\n");
	}
      destroy_satinstance_fully(s);
    }

    return 0;
}
 

