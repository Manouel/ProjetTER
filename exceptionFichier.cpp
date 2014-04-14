/*========================================================================
Nom: exceptionFichier.cpp           auteur: Jonathan Dufetel
Maj:  14/04/2014           Creation: 14/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation de la classe ExceptionFichier.
=========================================================================*/
#include "exceptionFichier.h"


using namespace std;

ExceptionFichier::ExceptionFichier() : contexteException(""){}

ExceptionFichier::ExceptionFichier(string contexte) : contexteException(contexte){}

ExceptionFichier::~ExceptionFichier() throw(){}

string ExceptionFichier::verdict() const throw(){
	return "contexte : "+contexteException;
}
