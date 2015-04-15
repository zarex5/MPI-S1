ROOT_SDL=/home/eleve/Bureau/exo2/rootSDL
INCDIR=$(ROOT_SDL)/include/SDL2
LIBDIR=$(ROOT_SDL)/lib

all : testdrawchessboard

testdrawchessboard : testdrawchessboard.c
	gcc -I$(INCDIR) -L$(LIBDIR) testdrawchessboard.c -o testdrawchessboard -lSDL2

