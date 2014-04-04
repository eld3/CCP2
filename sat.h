#ifndef SAT_H
#define SAT_H


#include <stdio.h>

typedef unsigned int variable;
typedef signed int literal;

typedef struct s_clause {
  unsigned int length;		/* number of literals */
  unsigned int size;		/* length of allocated space for literals */
  literal * lits;
} *clause;

typedef struct s_satinstance {
  unsigned int nclauses;	/* number of clauses */
  unsigned int size;		/* length of allocated space for clauses */
  clause *clauses;
} *satinstance;


/* Basic ADT functions */

/* functions for literals */
extern literal positive (variable x);
extern literal negative (variable x);
extern variable var(literal l);
extern int sign ( literal l);

/* functions for clauses */
extern clause empty_clause( void );
extern void add_literal( clause c, literal l);
unsigned int number_lits(clause c);
extern literal get_literal (clause c, unsigned int pos);
extern void destroy_clause ( clause c);

/* functions for whole SAT instances */
extern satinstance empty_satinstance( void );
extern void add_clause( satinstance s, clause  c);
extern unsigned int number_clauses(satinstance s);
extern clause get_clause (satinstance  s, unsigned int pos);
extern void destroy_satinstance ( satinstance s); /* does not destroy the clauses
						   because they might be shared */
extern void destroy_satinstance_fully ( satinstance s); /* does destroy the clauses
						   user must ensure that
						   they are not shared */

/* IO functions */
extern variable read_variable( FILE * f);/* as an integer */
extern literal read_literal( FILE * f);	/* as a signed integer */
extern clause read_clause ( FILE * f); /* literals in square brackets, comma separated */
extern satinstance read_satinstance ( FILE * f); /* clauses in curly
                                                    brackets, comma separated */

extern void write_variable ( FILE *f, variable x);
extern void write_literal ( FILE *f, literal l);
extern void write_clause ( FILE *f, clause c);
extern void write_satinstance ( FILE *f, satinstance  s);

/* Utility function */

extern variable largest_variable_clause(clause c);
extern variable largest_variable_satinstance(satinstance s);

/* Transformation Functions */
extern satinstance transform_to_3sat ( satinstance s);

#endif
  
