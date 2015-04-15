all : matrix 

ROOT_SDL=/home/eleve/Bureau/exo2/rootSDL
LIB=$(ROOT_SDL)/lib
INC=$(ROOT_SDL)/include/SDL2


matrix : matrix.c main.c
	gcc -L$(LIB) -I$(INC) main.c matrix.c -o matrix -lSDL2 -lSDL2_image -lSDL2_ttf

clean: 
	rm -rf matrix
