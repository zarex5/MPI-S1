//#define JULIUS_DEBUG

#ifdef JULIUS_DEBUG
	unsigned char mode_debug=1;	
#else
	unsigned char mode_debug=0;
#endif

#ifndef TEST_STRING
	#define TEST_STRING "Ceci est une chaine de test"
#endif

char * julius (const char * s, int decalage);
char * coder(char *s);
char * decoder(char *s);

