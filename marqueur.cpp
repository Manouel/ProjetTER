/*========================================================================
Nom: marqueur.cpp           auteur: Geoffrey DUMAS
Maj:  27/03/2014         Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation des fonctions de la classe Marqueur.
=========================================================================*/
#include <sstream>
#include "marqueur.h"

using namespace std;

template<typename TypeValeur>
Marqueur<TypeValeur>::Marqueur(){}

template<typename TypeValeur>
Marqueur<TypeValeur>::Marqueur(TypeValeur val) : valeur(val), orientation('+') {}

template<typename TypeValeur>
Marqueur<TypeValeur>::Marqueur(TypeValeur val, char ori) : valeur(val), orientation(ori) {}

template<typename TypeValeur>
Marqueur<TypeValeur>::Marqueur(const Marqueur& m) : valeur(m.valeur), orientation(m.orientation) {}

template<typename TypeValeur>
Marqueur<TypeValeur>::~Marqueur() {}

template<typename TypeValeur>
TypeValeur Marqueur<TypeValeur>::getValeur() const
{return this->valeur;}

template<typename TypeValeur>
char Marqueur<TypeValeur>::getOrientation() const
{return this->orientation;}

template<typename TypeValeur>
void Marqueur<TypeValeur>::setValeur(const TypeValeur& val)
{this->valeur= val;}

template<typename TypeValeur>
void Marqueur<TypeValeur>::setOrientation(char ori)
{this->orientation= ori;}

template<typename TypeValeur>
string Marqueur<TypeValeur>::toString() const
{
	stringstream ss;
	ss << this->orientation << this->valeur;
	
	return ss.str();
}

template<typename TypeValeur>
void Marqueur<TypeValeur>::saisie(istream& is){
	is>>valeur>>orientation;
}

template<typename TypeValeur>
void Marqueur<TypeValeur>::affiche(ostream& os)const{
	os<<getOrientation()<<getValeur(); 
}


template<typename TypeValeur>
bool operator== (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2){
	return (m1.getValeur() == m2.getValeur() && m1.getOrientation()==m2.getOrientation());
}

template<typename TypeValeur>
bool operator< (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2){
	if (m1.getValeur() < m2.getValeur())
		return true;
	else if (m1.getValeur() > m2.getValeur())
		return false;
	else
		return (m1.getOrientation() > m2.getOrientation());
}


