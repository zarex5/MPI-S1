# Objectif : reconstruire les executables shell et test
# à l'aide de la librairie julius 

INCDIR=./include
LIBDIR=./lib

all: bin/test_julius.exe bin/test_julius_static.exe 

# -I<chemin> permet d'indiquer à gcc le chemin de répertoires supplémentaires contenant des fichiers d'entête

build/test_julius.o : src/test_julius.c
	gcc -I$(INCDIR) -c src/test_julius.c -o build/test_julius.o

# -l<nomLib> permet de demander l'édition de liens avev la librairie lib<nomLib>.so ou lib<nomLib>.a

# -L<chemin> permet d'indiquer à gcc le chemin de répertoires supplémentaires contenant des librairies

bin/test_julius.exe : build/test_julius.o
	gcc -L$(LIBDIR) build/test_julius.o -o bin/test_julius.exe -ljulius

bin/test_julius_static.exe : build/test_julius.o
	gcc -L$(LIBDIR) -static build/test_julius.o -o bin/test_julius_static.exe -ljulius

# Pour executer le binaire lié dynamiquement, il faut penser à indiquer à l'OS où trouver les librairies situées dans des emplacements non standards. 

# On se place dans le répertoire lib, puis 
# export LD_LIBRARY_PATH=`pwd`
# crée la variable d'environnement permettant d'indiquer le chemin choisi à l'OS

clean: 
	rm -f bin/* build/*
