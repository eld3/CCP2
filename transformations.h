#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


#include <stdio.h>
#include "sat.h"
#include "graph.h"


/* Transformation Functions */
extern satinstance transform_to_3sat ( satinstance s);

extern graph transform_to_graph ( satinstance s);

extern satinstance transform_to_sat ( graph g);

/* Array Manipulation Functions */

int in_array(variable val, variable *array, int size);

void initialise_array( variable *array, int size);

#endif