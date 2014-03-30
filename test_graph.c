#include "graph.h"

main()
{
  graph g;
  vertex n, from, to, v;
  colour ncol;
  colouring cols;
  
  printf("Number vertices: ");
  scanf(" %u",&n);
  g = empty_graph(n,true);
  while (true)
    {
      printf("Add edge from to (0 0 to stop): ");
      scanf(" %u %u", &from, &to);
      if (from == 0 && to == 0)
	break;
      add_edge(g,from,to);
    }
  write_graph(stdout,g);
  printf("Max colours: ");
  scanf(" %u",&ncol);
  cols = colour_graph(g,ncol);
  if (cols != NULL)
    {
      printf("Colours:");
      for (v = 0; v < n; v++)
	{
	  printf(" %u",cols[v]);
	}
    }
  else
    printf("Can't colour");
  printf("\n");
}