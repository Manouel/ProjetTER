# Makefile de compilation du projet

CXX = g++
OBJS = main.o marqueur.o sequence.o adjacence.o alignement.o exceptionFichier.o logFichier.o marqueurType.o

FICHIERS_CPP = marqueur.cpp sequence.cpp adjacence.cpp alignement.cpp exceptionFichier.cpp logFichier.cpp marqueurType.cpp
FICHIERS_H = marqueur.h sequence.h adjacence.h alignement.h exceptionFichier.h logFichier.h

all : main libprojet.so interface

main : $(OBJS)
	$(CXX) -o main $(OBJS)

libprojet.so : $(FICHIERS_CPP) $(FICHIERS_H)
	$(CXX) -fPIC -shared -o libprojet.so $(FICHIERS_CPP)

interface :
	cd Interface && qmake && make


# Objets
	
main.o : main.cpp
	$(CXX) -o main.o -c main.cpp
	
marqueur.o : marqueur.cpp marqueur.h
	$(CXX) -o marqueur.o -c marqueur.cpp
	
sequence.o : sequence.cpp sequence.h
	$(CXX) -o sequence.o -c sequence.cpp
	
adjacence.o : adjacence.cpp adjacence.h
	$(CXX) -o adjacence.o -c adjacence.cpp
	
alignement.o : alignement.cpp alignement.h
	$(CXX) -o alignement.o -c alignement.cpp
	
exceptionFichier.o : exceptionFichier.cpp exceptionFichier.h
	$(CXX) -o exceptionFichier.o -c exceptionFichier.cpp
	
logFichier.o : logFichier.cpp logFichier.h
	$(CXX) -o logFichier.o -c logFichier.cpp
	
marqueurType.o : marqueurType.cpp
	$(CXX) -o marqueurType.o -c marqueurType.cpp
	
	

