
all : main libprojet.so fenetre

main : main.o marqueur.o sequence.o adjacence.o alignement.o exceptionFichier.o logFichier.o marqueurType.o
	g++ -o main main.o marqueur.o sequence.o adjacence.o alignement.o exceptionFichier.o logFichier.o marqueurType.o	
	
libprojet.so : main.o marqueur.o sequence.o adjacence.o alignement.o exceptionFichier.o logFichier.o marqueurType.o
	g++ -o libprojet.so -shared main.o marqueur.o sequence.o adjacence.o alignement.o exceptionFichier.o logFichier.o marqueurType.o

 

main.o : main.cpp
	g++ -c main.cpp

marqueur.o : marqueur.cpp marqueur.h
	g++ -c marqueur.cpp
	
sequence.o : sequence.cpp sequence.h
	g++ -c sequence.cpp
	
adjacence.o : adjacence.cpp adjacence.h
	g++ -c adjacence.cpp
	
alignement.o : alignement.cpp alignement.h
	g++ -c alignement.cpp
	
exceptionFichier.o : exceptionFichier.cpp exceptionFichier.h
	g++ -c exceptionFichier.cpp
	
logFichier.o : logFichier.cpp logFichier.h
	g++ -c logFichier.cpp

marqueurType.o : marqueurType.cpp
	g++ -c marqueurType.cpp
	
	
	
fenetre :
	(cd Interface && qmake && make)
	
	
