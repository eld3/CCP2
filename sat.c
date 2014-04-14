#include "sat.h"
#include <stdlib.h>
#include <ctype.h>

literal positive (variable x)
{
  return (literal) x;
}

literal negative (variable x)
{
  return -(literal) x;
}

variable var (literal l)
{
  return (variable)( (l > 0) ? l : -l);
}

int sign ( literal l)
{
  return  (l > 0) ? 1 : -1;
}


/* functions for clauses */

#define STARTING_CHUNK 10

clause empty_clause( void )
{
  clause c;
  c = (clause)malloc(sizeof(struct s_clause));
  c->length  = 0;
  c->size = STARTING_CHUNK;
  c->lits = (literal *)malloc(c->size * sizeof(literal));
  return c;
}

  
void add_literal( clause c, literal l)
{
  if (c->length == c->size)
    {
      c->size *= 2;
      c->lits = (literal *)realloc((void *)c->lits, c->size *sizeof(literal));
    }
  c->lits[c->length++] = l;
}

unsigned int number_lits(clause c)
{
  return c->length;
}

literal get_literal (clause c, unsigned int pos)
{
  if (pos >= number_lits(c))
    {
      fprintf(stderr,"Invalid access to literal %u of clause\n",pos);
      return 0;
    }
  return c->lits[pos];
}

void destroy_clause ( clause c)
{
  free((void *)c->lits);
  c->lits = NULL;
  free((void *)c);
}
  

/* functions for whole SAT instances */

satinstance empty_satinstance( void )
{
  satinstance s;
  s = (satinstance)malloc(sizeof(struct s_satinstance));
  s->nclauses  = 0;
  s->size = STARTING_CHUNK;
  s->clauses = (clause *)malloc(s->size * sizeof(clause));
  return s;
}

  
void add_clause( satinstance s, clause c)
{
  if (s->nclauses == s->size)
    {
      s->size *= 2;
      s->clauses = (clause *)realloc((void *)s->clauses, s->size *sizeof(clause));
    }
  s->clauses[s->nclauses++] = c;
}

unsigned int number_clauses(satinstance s)
{
  return s->nclauses;
}


clause get_clause (satinstance s, unsigned int pos)
{
  if (pos >= s->nclauses)
    {
      fprintf(stderr,"Invalid access to clause %u of satinstance\n",pos);
      return 0;
    }
  return s->clauses[pos];
}

extern void destroy_satinstance ( satinstance s)
{
  free((void *)s->clauses);
  s->clauses = NULL;
  free((void *)s);
}
  
extern void destroy_satinstance_fully ( satinstance s)
{
  unsigned int i;
  for (i = 0; i < number_clauses(s); i++)
    destroy_clause(get_clause(s,i));
  destroy_satinstance(s);
}
  

/* IO functions */
variable read_variable( FILE * f)
{
  variable x;
  if (1 != fscanf(f," %u",&x))
    {
      fprintf(stderr,"Can't read variable\n");
      return 0;
    }
  return x;
}

literal read_literal( FILE * f)
{
  literal l;
  if (1 != fscanf(f," %i",&l))
    {
      fprintf(stderr,"Can't read variable\n");
      return 0;
    }
  return l;
}

clause read_clause ( FILE * f)
{
  clause c;
  literal l;
  int ch;
  while (isspace(ch = getc(f)))
    ;
  if (ch != '[')
    {
      fprintf(stderr,"Syntax error, expecting [\n");
      return NULL;
    }
  c = empty_clause();
  do {
    while (isspace(ch = getc(f)))
      ;
    if (ch == ']')
      return c;
    ungetc(ch, f);
    l = read_literal(f);
    if (l == 0)
      {
	fprintf(stderr,"Syntax error reading clause\n");
	destroy_clause(c);
	return NULL;
      }
    add_literal(c,l);
    while (isspace(ch = getc(f)))
      ;
    if (ch != ',')
      ungetc(ch, f);
  } while (1);
        
}

extern satinstance read_satinstance ( FILE * f)
{
  satinstance s;
  clause c;
  int ch;
  while (isspace(ch = getc(f))) 
    ;
  if (ch != '{') 
    {
      fprintf(stderr,"Syntax error, expecting {\n"); 
      return NULL; 
    } 
  s = empty_satinstance();
  do { 
    while (isspace(ch = getc(f)))
      ;
    if (ch == '}')
      return s;
    ungetc(ch, f); 
    c = read_clause(f);
    if (c == NULL)
      {
	fprintf(stderr,"Syntax error reading satinsatnce\n");
	return NULL;
      }
    add_clause(s,c);
    while (isspace(ch = getc(f))) 
      ; 
    if (ch != ',') 
      ungetc(ch, f);
  } while (1);
}
        
 
void write_variable ( FILE *f, variable x)
{
  fprintf(f,"%u",x);
}

void write_literal ( FILE *f, literal l)
{
  fprintf(f,"%i",l);
}

void write_clause ( FILE *f, clause c)
{
  unsigned int i;
  unsigned int n = number_lits(c);
  fprintf(f,"[");
  for (i = 0; i < n; i++)
    {
      write_literal(f,get_literal(c,i));
      if (i < n - 1)
	fprintf(f,", ");
    }
  fprintf(f,"]");
}

void write_satinstance ( FILE *f, satinstance  s)
{
  unsigned int i;
  unsigned int n = number_clauses(s);
  fprintf(f,"{");
  for (i = 0; i < n; i++)
    {
      write_clause(f,get_clause(s,i));
      if (i < n - 1)
	fprintf(f,", ");
    }
  fprintf(f,"}");
}

variable largest_variable_clause(clause c)
{
  variable x = 0,y;
  unsigned int i;
  for (i = 0; i < number_lits(c); i++)
    {
      y = var(get_literal(c,i));
      if (y > x)
	x = y;
    }
  return x;
}

 variable largest_variable_satinstance(satinstance s)
{
  variable x = 0, y;
  unsigned int i;
  for (i = 0; i < number_clauses(s); i++)
    {
      y = largest_variable_clause(get_clause(s,i));
      if (y > x)
	x = y;
    }
  return x;
}

  
