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
	$(CXX) -c main.cpp
	
marqueur.o : marqueur.cpp marqueur.h
	$(CXX) -c marqueur.cpp
	
sequence.o : sequence.cpp sequence.h
	$(CXX) -c sequence.cpp
	
adjacence.o : adjacence.cpp adjacence.h
	$(CXX) -c adjacence.cpp
	
alignement.o : alignement.cpp alignement.h
	$(CXX) -c alignement.cpp
	
exceptionFichier.o : exceptionFichier.cpp exceptionFichier.h
	$(CXX) -c exceptionFichier.cpp
	
logFichier.o : logFichier.cpp logFichier.h
	$(CXX) -c logFichier.cpp
	
marqueurType.o : marqueurType.cpp
	$(CXX) -c marqueurType.cpp
	
	

