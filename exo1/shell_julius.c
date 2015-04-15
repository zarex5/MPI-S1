#include <stdio.h>
#include <stdlib.h>
#include "julius.h"

int main(int argc, char ** argv)
{
	char * s; 
	if (argc < 2)
	{
		fprintf(stderr,"julius <chaine> <decalage>\n");
		return 1; 
	}
	s = julius(argv[1], atoi(argv[2]));
	printf("%s\n",s);

	return 0;
}
