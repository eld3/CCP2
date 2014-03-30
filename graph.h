#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef unsigned int vertex;
typedef unsigned int bool;
#define true ((bool)1)
#define false ((bool)0)

typedef struct s_graph {
  vertex numvertices;
  bool undirected;
  bool **adjacency;
} *graph;

extern graph empty_graph( vertex numvertices, bool undirected );
extern vertex number_vertices(graph g);
extern void add_edge( graph g, vertex from, vertex to );
extern bool is_adjacent( graph g, vertex from, vertex to );
extern void destroy_graph ( graph g );
extern void write_graph ( FILE *f, graph g);

typedef unsigned int colour;
typedef colour *colouring;

extern colouring colour_graph( graph g, colour ncols );

#endif