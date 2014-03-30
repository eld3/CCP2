#include "graph.h"
#include <stdlib.h>


graph empty_graph( vertex numvertices, bool undirected )
{
  graph g;
  vertex v;
  vertex w;
  g = (graph) malloc(sizeof(struct s_graph));
  g->numvertices = numvertices;
  g->undirected = undirected;
  g->adjacency = (bool **)malloc(sizeof(bool *)*numvertices);
  for (v = 0; v < numvertices; v++)
    {
      g->adjacency[v] = (bool *)malloc(sizeof(bool)*numvertices);
      for (w = 0; w < numvertices; w++)
	g->adjacency[v][w] = false;
    }
  return g;
}

void add_edge( graph g, vertex from, vertex to )
{
  if (from >= g->numvertices || to >= g->numvertices)
    {
      fprintf(stderr, "Vertex out of range\n");
      return;
    }
  if (g->adjacency[from][to] )
    {
      fprintf(stderr, "Edge already present %u %u\n",from,to);
      return;
    }
  if (from == to)
    {
      fprintf(stderr, "Loops not allowed\n");
      return;
    }
    
  g->adjacency[from][to] = true;
  if (g->undirected)
    g->adjacency[to][from] = true;
  return;
}

bool is_adjacent( graph g, vertex from, vertex to )
{
  if (from >= g->numvertices || to >= g->numvertices)
    {
      fprintf(stderr, "Vertex out of range\n");
      return false;
    }
  return g->adjacency[from][to];
}

void destroy_graph ( graph g )
{
  vertex v;
  for (v = 0; v < g->numvertices; v++)
    {
      free((void *)g->adjacency[v]);
      g->adjacency[v] = NULL;
    }
  free((void *)g->adjacency);
  g->adjacency = NULL;
  free((void *)g);
}

void write_graph ( FILE *f, graph g)
{
  vertex v,w;
  fprintf(f, "%s graph %u vertices, adjacencies:\n",
	  g->undirected ? "Undirected" : "Directed",
	  g->numvertices);
  for (v = 0; v < g->numvertices; v++)
    {
      fprintf(f,"  %u:",v);
      for (w = 0; w < g->numvertices; w++)
	if (g->adjacency[v][w])
	  fprintf(f, " %u",w);
      fprintf(f,"\n");
    }
  fprintf(f,"\n");
  return;
}


colouring colour_graph( graph g, colour ncols )
{
  vertex v = 0, n = g->numvertices,w;
  colouring work = (colouring)malloc(sizeof(colour)*n);
  unsigned int *colour_count = (unsigned int *)malloc(sizeof(unsigned int)*ncols);
  colour col;
  for (col = 0; col < ncols; col++)
    colour_count[col] = 0;
  work[0] = 0;
  colour_count[0] = 1;
  while (v < n)
    {
      /* look for a colour clash */
      for (w = 0; w < v; w++)
	{
	  if (work[w] == work[v] &&
	      is_adjacent(g,v,w))
	    break;
	}
      
      if (w < v)		/* did we find one */
	{
	  /* have we run out of colours? */
	  while (0 == --colour_count[work[v]] || ++work[v] == ncols)
	    {
	      /* have we also backtracked as far as we can? */
	      if (v == 0)
		{
		  /* if so then there is no colouring */
		  free((void *)work);
		  free((void *)colour_count);
		  return NULL;
		}
	      else
		/* backtrack */
		v--;
	    }

	  /* Now finish the book-keeping and try the new combination */  
	  colour_count[work[v]]++;
	}
      else /* looks OK so far  try and complete the colouring*/
	{
	  v++;
	  if (v < n)
	    {
	      work[v] = 0;
	      colour_count[0]++;
	    }
	}
    }
  /* here with a successful colouring */
  free((void *)colour_count);
  return work;
}
      
vertex number_vertices(graph g)
{
  return g->numvertices;
}