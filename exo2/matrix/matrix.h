#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>


/**	Variante de la macro CHECK définie dans les TP précédents.
 *	Lorsque stat vaut val alors l'opération dont le résultat
 *	est stat, a échoué.
 *	Pour la plupart des appels SDL, la valeur signalant 
 *	l'échec est un entier négatif. Elle correspond à NULL lorsque l'appel système
 *	retourne un pointeur. 
 */
#ifdef	_DEBUG
#define CHECK_IF(stat, val, msg)    \
	if ( (stat) == (val) )          \
	{                               \
    	perror(msg);                \
		exit( EXIT_FAILURE );       \
    }                       
#else
#define CHECK_IF(stat, val, msg)    \
	if ( (stat) == (val) )          \
	{                               \
    	perror(msg);                \
		exit( EXIT_FAILURE );       \
    }                               \
    else printf("%s ... OK\n", msg)

#endif

// Taille de la fenêtre, si pas fullscreen
#ifndef WIN_WIDTH
	#define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
	#define WIN_HEIGHT 500
#endif

#ifndef SIZE_ICO 
	#define SIZE_ICO 64
#endif

#ifndef NB_COLS 
	#define NB_COLS 32
#endif

#ifndef NB_ROWS 
	#define NB_ROWS 16
#endif

#ifndef TITLE
	#define TITLE "MPI - IG2I 2015"
#endif

#ifndef FONT_PATH
	#define FONT_PATH "polices/galacticstorm.ttf"
#endif

#ifndef FIXED_FONT_PATH
	#define FIXED_FONT_PATH "polices/whitrabt.ttf"
#endif

// Taille de la zone de jeu = fonction taille fenetre et nb de panneaux... 
// Par défaut, no_panel mais grille active 
enum E_CONFIG {NO_PANEL=0, TITLE_PANEL=1<<0, RIGHT_PANEL=1<<1, BOTTOM_PANEL=1<<2, LEFT_PANEL=1<<3, NO_GRID=1<<4, GRID_COORDS=1<<5};
enum E_STATUS {PRE_INIT=0, INIT_DONE=1};

typedef struct {
	unsigned char r; 
	unsigned char g; 
	unsigned char b;
	unsigned char a;
} T_COLOR; 

enum E_COLOR {BLACK=0,RED,GREEN,BLUE,WHITE};



// Le programme s'exécute au plus 10 secondes, sauf si la constante INFINITE_EXECUTION_TIME est activée
// #define INFINITE_EXECUTION_TIME
#ifndef MAX_EXECUTION_TIME 
	#define MAX_EXECUTION_TIME 10
#endif

// Initialise ce qu'il faut pour avoir une fenêtre
// Définit les panneaux souhaités à l'aide d'un ou logique 
// On crée des variables globales pour récupérer les adresses des structures définies

#define CHK_CONFIG(i,panel2chk)  ( ((i & panel2chk) !=0) || (i == panel2chk))
#define MIN(a,b) ((a <= b) ? a : b)
#define MAX(a,b) ((a >= b) ? a : b)

typedef struct {
	unsigned char status; 
	unsigned int nbCols; 
	unsigned int nbRows; 
	unsigned char pxByLed; 
	unsigned char hasGrid;
	unsigned char hasTitle;
	unsigned char hasRightPanel;
	unsigned char hasBottomPanel;
	unsigned char hasLeftPanel;
	unsigned int wGrid; 			// hors tout: y compris les pixels de la grille elle-même
	unsigned int hGrid;
	unsigned int xStartGrid; 
	unsigned int yStartGrid;
	unsigned int dispoW;		// espace inutilisé pour résoudre les pbs d'arrondis
	unsigned int dispoH;
	unsigned int hasCoords;

} T_Config; 

 

void matrix_init(int panels);
void showTitle(SDL_Renderer *renderer, SDL_Surface *surface);
void showPanels(SDL_Renderer *renderer, SDL_Surface *surface);
void setLed(SDL_Renderer *renderer,unsigned int i, unsigned int j, unsigned char color);
void clearLed(SDL_Renderer *renderer,unsigned int i, unsigned int j);
void showGrid(SDL_Renderer *renderer, SDL_Surface *surface);
void showImg(SDL_Surface *surface);

