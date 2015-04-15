#fichier makefile: définit des règles de production
#format d'un règle :
# <cible> : <dépendance1> <dépendance2> ...
# TAB <règle de production 1>
# TAB <règle de production 2>

	# (1) Execution: make <cible>, ou juste make pour executer la règle par defaut
	# Premiere regle du fichier makefile: règle par defaut (ici all)

	# (2) Pour s'arreter à l'étape de compilation,
	# on utilise l'option -c
	
	# (3) Pour réaliser l'édition de liens,
	# il suffit d'utiliser gcc avec les fichiers objets compilés précédement

	# (4) Pour réaliser une édition de liens statique,
	# on utilise l'option -static
	
	# (5.1) Une librairie statique est une archive de fichiers objets
	# produite avec l'archiveur 'ar'
	
	# (5.2) Une librairie dynamique est produite
	# par compilation avec l'option fPIC
	# et édition de liens avec l'option -shared

#1	
all : no_debug debug alt_string objs mod lib

alt_string : test_julius_alt_string.exe
no_debug : test_julius.exe shell_julius.exe
debug : test_julius_debug.exe shell_julius_debug.exe
objs : julius.o test_julius.o shell_julius.o
mod: test_julius_modulaire.exe shell_julius_modulaire.exe
static: test_julius_static.exe shell_julius_static.exe
lib : libjulius.so libjulius.a



#2
test_julius.o : julius.h test_julius.c
	gcc -c test_julius.c -o test_julius.o

shell_julius.o : julius.h shell_julius.c
	gcc -c shell_julius.c -o shell_julius.o
	
julius.o : julius.c
	gcc -c julius.c -o julius.o
	
	
	
#3	
test_julius_modulaire.exe : test_julius.o julius.o
	gcc test_julius.o julius.o -o test_julius_modulaire.exe

shell_julius_modulaire.exe : shell_julius.o julius.o
	gcc shell_julius.o julius.o -o shell_julius_modulaire.exe
	
	
	
#4	
test_julius_static.exe : test_julius.o julius.o
	gcc -static test_julius.o julius.o -o test_julius_static.exe

shell_julius_static.exe : shell_julius.o julius.o
	gcc -static shell_julius.o julius.o -o shell_julius_static.exe
	
	
	
#0	
test_julius_alt_string.exe : julius.c julius.h test_julius.c
	gcc -D'TEST_STRING="autre chaine"' julius.c test_julius.c -o test_julius_alt_string.exe
	
	
test_julius_debug.exe : julius.c julius.h test_julius.c
	gcc -DJULIUS_DEBUG julius.c test_julius.c -o test_julius_debug.exe
	
shell_julius_debug.exe : julius.c julius.h shell_julius.c
	gcc -DJULIUS_DEBUG julius.c shell_julius.c -o shell_julius_debug.exe

test_julius.exe : julius.c julius.h test_julius.c
	gcc julius.c test_julius.c -o test_julius.exe
	
shell_julius.exe : julius.c julius.h shell_julius.c
	gcc julius.c shell_julius.c -o shell_julius.exe	
	
	
	
#5.1
libjulius.a : julius.o
	ar -qvs libjulius.a julius.o


#5.2
libjulius.so : julius.c
	gcc -c -fPIC julius.c -o julius.fPIC.o
	gcc -shared julius.fPIC.o -o libjulius.so

	
#+
clean:
	rm -f *.exe *.o

cleanall:
	rm -f *.exe *.o *.so *.a
