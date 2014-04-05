#ifndef SAT_H
#define SAT_H


#include <stdio.h>
#include "sat.h"
#include "graph.h"


/* Transformation Functions */
extern satinstance transform_to_3sat ( satinstance s);

extern void transform_to_graph ( satinstance s);

extern satinstance transform_to_sat ( graph g);

#endif