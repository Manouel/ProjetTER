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
void Marqueur<TypeValeur>::setValeur(TypeValeur val)
{this->valeur= val;}

template<typename TypeValeur>
void Marqueur<TypeValeur>::setOrientation(char ori)
{this->orientation= ori;}

template<typename TypeValeur>
void Marqueur<TypeValeur>::saisie(istream& is){
	is>>valeur>>orientation;
}

template<typename TypeValeur>
void Marqueur<TypeValeur>::affiche(ostream& os)const{
	os<<getOrientation()<<" "<<getValeur()<<endl; 
}

template<typename TypeValeur> //A enlever ? 
bool operator== (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2){
	return (m1.getValeur() == m2.getValeur() && m1.getOrientation()==m2.getOrientation());
}


