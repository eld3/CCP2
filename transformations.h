#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


#include <stdio.h>
#include "sat.h"
#include "graph.h"


/* Transformation Functions */
extern satinstance transform_to_3sat ( satinstance s);

extern graph transform_to_graph ( satinstance s, variable *v, int num_var);

extern satinstance transform_to_sat ( graph g);

/* Array Manipulation Functions */

int in_array(variable val, variable *array, int size);

void initialise_array( variable *array, int size);

int get_number_variables( variable *array);

variable* create_variable_array(satinstance s);

#endif