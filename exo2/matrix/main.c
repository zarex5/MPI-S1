#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>

#include <SDL.h>
#include "matrix.h"

extern T_Config mpi_cfg ;


int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Renderer *renderer;

	// SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	/* Initialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return 1;
	}

	/* Create window and renderer for given surface */
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
		return 1;
	}	

	//SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
	surface = SDL_GetWindowSurface(window);

	renderer = SDL_CreateSoftwareRenderer(surface);
	if(!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
		return 1;
	}

	// Use this function to set the color used for drawing operations (Rect, Line and Clear). 
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	// Use this function to clear the current rendering target with the drawing color. 
	SDL_RenderClear(renderer);

	if(TTF_Init() == -1)
	{
		 fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		 exit(EXIT_FAILURE);
	} 

	SDL_UpdateWindowSurface(window);

	matrix_init(LEFT_PANEL|TITLE_PANEL|GRID_COORDS);

	showGrid(renderer, surface);
	showPanels(renderer,surface);
	showTitle(renderer, surface);
	showImg(surface);

	unsigned int currentX=1,currentY=2; 
	unsigned int lastX=1,lastY=2; 
	
	

	while(1)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			//printf("%d\n",e.key.keysym.sym);

			if (e.type == SDL_QUIT) 
				break;

			if(e.key.keysym.sym == SDLK_RIGHT)	{
				currentX  = (lastX+1)% mpi_cfg.nbCols;
			}

			if(e.key.keysym.sym == SDLK_LEFT)	{
				currentX  = (lastX+mpi_cfg.nbCols-1) %mpi_cfg.nbCols;
			}

			if(e.key.keysym.sym == SDLK_DOWN)	{
				currentY  = (lastY+1) % mpi_cfg.nbRows;
			}

			if(e.key.keysym.sym == SDLK_UP)	{
				currentY  = (lastY+mpi_cfg.nbRows-1) % mpi_cfg.nbRows;
			}
				
		}

		clearLed(renderer,lastX,lastY);			
		setLed(renderer,currentX,currentY,RED);	
		lastX = currentX; 
		lastY = currentY;

		SDL_UpdateWindowSurface(window);

	}

	return 0;
}

