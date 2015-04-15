#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern unsigned char mode_debug;

char * julius (const char * s, int decalage)
{
	int taille=0,i=0;
	char * aux = NULL;

	if (mode_debug) printf("\n---\njulius '%s' %d\n",s,decalage);

	taille = strlen(s); 
	if (mode_debug) printf("\tAllocation %d octets: ",taille);
	aux = (char * ) malloc (sizeof(char) * taille);
	if (mode_debug) printf("ok\n");

	if (mode_debug) printf("\tEncodage: ");
	for(i=0;i<taille;i++)
	{
		if ((s[i]>='A') && (s[i]<='Z'))
			aux[i] = ((s[i] -'A') + 26 - decalage)%26  +'a'; 
		else if ((s[i]>='a') && (s[i]<='z'))
			aux[i] = ((s[i] -'a') + 26 - decalage)%26  +'A';
		else aux[i] = s[i];
	}
	aux[i] = '\0';

	if (mode_debug) printf("ok\n");
	if (mode_debug) printf("\tResultat: %s\n---\n\n",aux);

	return aux;
}

char * coder(char *s) {
	return julius(s,3);
}

char * decoder(char *s) {
	return julius(s,-3);
}

