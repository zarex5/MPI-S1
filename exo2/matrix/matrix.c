#include "matrix.h"

T_Config mpi_cfg ={0} ;
T_COLOR couleurs[] = {{0,0,0,0},{0xFF,0,0,0},{0,0xFF,0,0},{0,0,0xFF,0},{0xFF,0xFF,0xFF}};

void showTitle(SDL_Renderer *renderer, SDL_Surface *surface) {
	SDL_Rect aux;

if (!mpi_cfg.hasTitle) return;

		aux.x =mpi_cfg.xStartGrid ; 
		aux.y = mpi_cfg.dispoH/4; 
		aux.h =SIZE_ICO; 
		aux.w = mpi_cfg.wGrid ;

		TTF_Font *police = NULL;
		police = TTF_OpenFont(FONT_PATH, 10);

		int w10,h10,w,h;
		TTF_SizeText(police,TITLE,&w10,&h10);
		TTF_CloseFont(police);

		printf("taille : %d\n",MIN(aux.w/w10,aux.h/h10));
		police = TTF_OpenFont(FONT_PATH,	10 * MIN(aux.w/w10,aux.h/h10));
		TTF_SizeText(police,TITLE,&w,&h);

		aux.x =mpi_cfg.xStartGrid + (mpi_cfg.wGrid-w)/2 ; 
		aux.y = mpi_cfg.dispoH/4 + (SIZE_ICO-h)/2; 
		aux.h = h; 
		aux.w = w;

		SDL_Color color={0xFF,0xFF,0xFF};
		SDL_Surface *text_surface;
		text_surface=TTF_RenderText_Solid(police,TITLE,color);
		SDL_BlitSurface(text_surface,NULL,surface,&aux);

}


void showPanels(SDL_Renderer *renderer, SDL_Surface *surface) {
	SDL_Rect aux; 
	// Affiche des rectangles pour les panneaux si besoin 
	if (mpi_cfg.hasLeftPanel) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		aux.x =mpi_cfg.dispoW/4 ; 
		aux.y = mpi_cfg.yStartGrid; 
		aux.w =SIZE_ICO; 
		aux.h = mpi_cfg.hGrid ;
		SDL_RenderDrawRect(renderer,&aux ); 
	}

	if (mpi_cfg.hasRightPanel) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		aux.x =mpi_cfg.wGrid + mpi_cfg.hasLeftPanel * SIZE_ICO + 3*mpi_cfg.dispoW/4 ; 
		aux.y = mpi_cfg.yStartGrid; 
		aux.w =SIZE_ICO; 
		aux.h = mpi_cfg.hGrid ;
		SDL_RenderDrawRect(renderer,&aux ); 
	}

	if (mpi_cfg.hasBottomPanel) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		aux.x =mpi_cfg.xStartGrid ; 
		aux.y= mpi_cfg.hGrid + mpi_cfg.hasTitle * SIZE_ICO + 3 * mpi_cfg.dispoH/4 ; 
		aux.h =SIZE_ICO; 
		aux.w = mpi_cfg.wGrid ;
		SDL_RenderDrawRect(renderer,&aux ); 
	}

}

void showImg(SDL_Surface *surface) {
	SDL_Rect aux;
	aux.x =mpi_cfg.dispoW/4 ; 
	aux.y = mpi_cfg.yStartGrid; 
	aux.w =SIZE_ICO; 
	aux.h = SIZE_ICO ;

	SDL_Surface *image;
	image=IMG_Load("images/33.png");
	SDL_BlitSurface(image,NULL,surface,&aux);
}

void setLed(SDL_Renderer *renderer,unsigned int i, unsigned int j, unsigned char color){	
	SDL_SetRenderDrawColor(renderer, couleurs[color].r,couleurs[color].g,couleurs[color].b,couleurs[color].a);
	SDL_Rect aux;
	aux.x = mpi_cfg.xStartGrid+ mpi_cfg.hasCoords* (mpi_cfg.pxByLed+2) + i* (mpi_cfg.pxByLed+1); 
	aux.y = mpi_cfg.yStartGrid+ mpi_cfg.hasCoords* (mpi_cfg.pxByLed+2) + j* (mpi_cfg.pxByLed+1); 
	aux.w = mpi_cfg.pxByLed; 
	aux.h = mpi_cfg.pxByLed;

	SDL_RenderFillRect(renderer,&aux);

}

void clearLed(SDL_Renderer *renderer,unsigned int i, unsigned int j) {
	setLed(renderer,i,j,BLACK);
}

void showGrid(SDL_Renderer *renderer, SDL_Surface *surface){

	if (mpi_cfg.status != INIT_DONE) {
		printf("mpi_init not called !");
		return; 
	}

	int i, j; 
	SDL_Rect aux;
	char buf[4];

	
	TTF_Font *police = NULL;
	police = TTF_OpenFont(FIXED_FONT_PATH, 10);

	int w10,h10,w2,h2,w1,h1;
	TTF_SizeText(police,"00",&w10,&h10);
	TTF_CloseFont(police);

	police = TTF_OpenFont(FIXED_FONT_PATH,	10 * MIN((mpi_cfg.pxByLed)/w10,(mpi_cfg.pxByLed)/h10));
	TTF_SizeText(police,"00",&w2,&h2);
	TTF_SizeText(police,"0",&w1,&h1);

	SDL_Color color={0xFF,0xFF,0xFF};
	SDL_Surface *text_surface;


	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	for(i=mpi_cfg.hasCoords;i<=mpi_cfg.nbCols;i++) 
	{
		SDL_RenderDrawLine(renderer,
				mpi_cfg.xStartGrid+ i* (mpi_cfg.pxByLed+1),
				mpi_cfg.yStartGrid+ mpi_cfg.hasCoords* (mpi_cfg.pxByLed+1),
				mpi_cfg.xStartGrid+ i* (mpi_cfg.pxByLed+1),
				mpi_cfg.yStartGrid+mpi_cfg.hGrid-1);

		if (mpi_cfg.hasCoords && (i!=mpi_cfg.nbCols)) {
			aux.x =mpi_cfg.xStartGrid + i* (mpi_cfg.pxByLed+1) + (mpi_cfg.pxByLed - ((i>10)?w2:w1))/2; 
			aux.y = mpi_cfg.yStartGrid + (mpi_cfg.pxByLed - h1)/2; 
			aux.h = h1; 
			aux.w = (i>10)?w2:w1;
			sprintf(buf,"%d",i-1); 
			text_surface=TTF_RenderText_Solid(police,buf,color);
			SDL_BlitSurface(text_surface,NULL,surface,&aux);
		}
	}
	for(j=mpi_cfg.hasCoords;j<=mpi_cfg.nbRows;j++) 
	{
		SDL_RenderDrawLine(renderer,
				mpi_cfg.xStartGrid+ mpi_cfg.hasCoords* (mpi_cfg.pxByLed+1),
				mpi_cfg.yStartGrid+ j* (mpi_cfg.pxByLed+1),
				mpi_cfg.xStartGrid+mpi_cfg.wGrid-1,
				mpi_cfg.yStartGrid+ j* (mpi_cfg.pxByLed+1));

		if (mpi_cfg.hasCoords && (j!=mpi_cfg.nbRows)) {
			aux.x =mpi_cfg.xStartGrid + (mpi_cfg.pxByLed - ((i>10)?w2:w1))/2; 
			aux.y = mpi_cfg.yStartGrid + j* (mpi_cfg.pxByLed+1) + (mpi_cfg.pxByLed - h1)/2; 
			aux.h = h1; 
			aux.w = (i>10)?w2:w1;
			sprintf(buf,"%d",j-1); 
			text_surface=TTF_RenderText_Solid(police,buf,color);
			SDL_BlitSurface(text_surface,NULL,surface,&aux);
		}
	}

}

void matrix_init(int panels) {

	// Si Fullscreen, On récupère les dimensions dispo de l'écran qui écrasent les dimensions à produire
	// Sinon, les dimensions à produire sont celles demandées par l'utilisateur 
	// Elles servent à créer plusieurs zones en fonctions des panneaux requis
	// Il faut toutefois faire attention au nombre de cases requises car le nb de pixels peut ne pas tomber juste... 
	// Nos diodes sont toujours carrées : PX_PAR_LED pixels de côté
	// ON peut choisir d'afficher la grille ou pas
	// Si la grille est affichée, elle utilise toujours 1 pixel de large
	// Soit NB_COL+1 pixels pour la grille 
	// + NB_COL * PX_PAR_LED
	// + {0,1,2} * SIZE_ICO  = largeur écran 
	// Deux inconnues : PX_PAR_LED et SIZE_ICO
	// On fait l'hypothèse qu'un panneau fait toujours la même largeur en pixels, e.g. 32x32, 48x48...
	// défini dans SIZE_ICO

	//  NB_COL+1+NB_COL*PX_PAR_LED+k*SIZE_ICO <= EWIDTH
	// PX_PAR_LED <= (EWIDTH - k*SIZE_ICO - NB_COL+1) / NB_COL

	int nbPanW=0; 
	int nbPanH=0; 

	if (CHK_CONFIG(panels,NO_GRID)) mpi_cfg.hasGrid = 0;  else mpi_cfg.hasGrid = 1;
	if (CHK_CONFIG(panels,TITLE_PANEL)) {mpi_cfg.hasTitle = 1;nbPanH++;}  else mpi_cfg.hasTitle = 0;
	if (CHK_CONFIG(panels,RIGHT_PANEL)) {mpi_cfg.hasRightPanel = 1;nbPanW++;}  else mpi_cfg.hasRightPanel = 0; 
	if (CHK_CONFIG(panels,BOTTOM_PANEL)) {mpi_cfg.hasBottomPanel = 1;nbPanH++;}  else mpi_cfg.hasBottomPanel = 0;
	if (CHK_CONFIG(panels,LEFT_PANEL)) {mpi_cfg.hasLeftPanel = 1;nbPanW++;}  else mpi_cfg.hasLeftPanel = 0; 
	if (CHK_CONFIG(panels,GRID_COORDS)) {mpi_cfg.hasCoords = 1;}  else mpi_cfg.hasCoords = 0; 

	mpi_cfg.nbCols = NB_COLS+mpi_cfg.hasCoords; 
	mpi_cfg.nbRows = NB_ROWS+mpi_cfg.hasCoords; 

	// Comment choisir quelles options doivent être passées en arguments dans le code 
	// et lesquelles sont passées par constantes ? 
	// Les pbs de tailles sont fonction de l'écran => constantes symboliques; 
	// les pbs de panneaux et grilles sont fonction de l'IHM => paramètres

	// Calculs fenêtrés
	int max1_pxByLed = (WIN_WIDTH - nbPanW * SIZE_ICO - mpi_cfg.hasGrid * (mpi_cfg.nbCols+1)) / mpi_cfg.nbCols ;
	int max2_pxByLed = (WIN_HEIGHT - nbPanH * SIZE_ICO - mpi_cfg.hasGrid * (mpi_cfg.nbRows+1)) / mpi_cfg.nbRows ; 

	printf("%d x %d (%d * %d)\n", WIN_WIDTH, WIN_HEIGHT,mpi_cfg.nbCols, mpi_cfg.nbRows);
	printf("max1 pxByLed H : %d\n", max1_pxByLed);
	printf("max2 pxByLed H : %d\n", max2_pxByLed);

	mpi_cfg.pxByLed = MIN(max1_pxByLed,max2_pxByLed); 
	// On reconstruira l'affichage sur cette base

	mpi_cfg.wGrid = mpi_cfg.nbCols * mpi_cfg.pxByLed + mpi_cfg.hasGrid * (mpi_cfg.nbCols+1);
	mpi_cfg.hGrid = mpi_cfg.nbRows * mpi_cfg.pxByLed + mpi_cfg.hasGrid * (mpi_cfg.nbRows+1);

	// La grille commence en fonction des panneaux choisis
	// même s'il n'y a pas de panneaux, il ne faut peut-être pas coller à la marge ! 
	mpi_cfg.dispoW = WIN_WIDTH - mpi_cfg.wGrid - nbPanW * SIZE_ICO; 
	mpi_cfg.dispoH = WIN_HEIGHT - mpi_cfg.hGrid - nbPanH * SIZE_ICO; 

	mpi_cfg.xStartGrid = mpi_cfg.hasLeftPanel * SIZE_ICO + mpi_cfg.dispoW/2;
	mpi_cfg.yStartGrid =  mpi_cfg.hasTitle * SIZE_ICO + mpi_cfg.dispoH/2;

	mpi_cfg.status = INIT_DONE;


	// On interdit qu programme de fonctionner plus d'un certain temps
	#ifndef INFINITE_EXECUTION_TIME
		alarm(MAX_EXECUTION_TIME);
	#endif


}


