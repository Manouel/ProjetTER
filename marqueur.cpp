/*========================================================================
Nom: marqueur.cpp           auteur: Geoffrey DUMAS
Maj:  13/02/2014         Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation des fonctions de la classe Marqueur.
=========================================================================*/
#include "marqueur.h"

using namespace std;

Marqueur::Marqueur(){}
Marqueur::Marqueur(int val) : valeur(val), orientation('+') {}
Marqueur::Marqueur(int val, char ori) : valeur(val), orientation(ori) {}
Marqueur::Marqueur(const Marqueur& m) : valeur(m.valeur), orientation(m.orientation) {}

Marqueur::~Marqueur() {}

int Marqueur::getValeur() const
{return this->valeur;}

char Marqueur::getOrientation() const
{return this->orientation;}

void Marqueur::setValeur(int val)
{this->valeur= val;}

void Marqueur::setOrientation(char ori)
{this->orientation= ori;}

void Marqueur::saisie(istream& is){
	is>>valeur>>orientation;
}

void Marqueur::affiche(ostream& os)const{
	os<<this->getOrientation()<<" "<<this->getValeur()<<endl; 
}

bool operator== (const Marqueur& m1, const Marqueur& m2){
	return (m1.getValeur() == m2.getValeur() && m1.getOrientation()==m2.getOrientation());
}


