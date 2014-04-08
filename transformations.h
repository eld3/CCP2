#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


#include <stdio.h>
#include "sat.h"
#include "graph.h"


/* Transformation Functions */
extern satinstance transform_to_3sat ( satinstance s);

extern graph transform_to_graph ( satinstance s, variable *v, int num_var);

extern satinstance transform_to_sat ( graph g);

extern void print_sat_solutions( colouring cols, int num_var, satinstance s, variable *array);

extern int in_y_value(colouring cols, colour c, int num_var);

extern int find_false_colour(colouring cols, int num_var);

/* Array Manipulation Functions */

int in_array(variable val, variable *array, int size);

void initialise_array( variable *array, int size);

int get_number_variables( variable *array);

variable* create_variable_array(satinstance s);

#endif