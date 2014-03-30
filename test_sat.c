#include "sat.h"

main()
{
  satinstance s;
  while(1)
    {
      printf("Instance: ");
      s = read_satinstance(stdin);
      if (s)
	{
	  write_satinstance(stdout,s);
	  printf("\n");
	  printf("Last variable %u\n\n",largest_variable_satinstance(s));
	}
      destroy_satinstance_fully(s);
    }
}
 






