#include <stdio.h>
#include <stdlib.h>
#include "julius.h"

int main(void)
{
	char * s; 
	s = coder(TEST_STRING); 
	printf("Encodage de '%s' : '%s'\n",TEST_STRING,s);
	printf("Decodage de '%s' : '%s'\n",s,decoder(s));

	return 0;
}
