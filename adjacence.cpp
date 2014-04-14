/*========================================================================
Nom: adjacence.cpp           auteur: Morgane Vidal
Maj:  27/03/2014         Creation: 13/02/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation des fonctions de la classe Adjacence.
=========================================================================*/
#include <iostream>
#include "adjacence.h"

using namespace std;

template<typename TypeValeur>
Adjacence<TypeValeur>::Adjacence(){}

template<typename TypeValeur>
Adjacence<TypeValeur>::Adjacence(Marqueur<TypeValeur> m1, Marqueur<TypeValeur> m2) : marqueur1(m1), marqueur2(m2) {}

template<typename TypeValeur>
Adjacence<TypeValeur>::~Adjacence() {}

template<typename TypeValeur>
Marqueur<TypeValeur> Adjacence<TypeValeur>::getMarqueur1() const{
	return this->marqueur1;
}

template<typename TypeValeur>
Marqueur<TypeValeur> Adjacence<TypeValeur>::getMarqueur2() const{
	return this->marqueur2;	
}

template<typename TypeValeur>
void Adjacence<TypeValeur>::affiche() const{
	cout << "(" << marqueur1.getOrientation() << marqueur1.getValeur() << "|" << marqueur2.getOrientation() << marqueur2.getValeur() << ")"<<endl;
}

template<typename TypeValeur>
bool operator== (const Adjacence<TypeValeur>& a1, const Adjacence<TypeValeur>& a2){

	if(a1.getMarqueur1()==a2.getMarqueur1())
	{
		if(a1.getMarqueur2()==a2.getMarqueur2())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(a1.getMarqueur1().getValeur()==a2.getMarqueur2().getValeur())
		{
			if(a1.getMarqueur2().getValeur()==a2.getMarqueur1().getValeur())
			{
				if(a1.getMarqueur1().getOrientation()!=a2.getMarqueur2().getOrientation())
				{
					if(a1.getMarqueur2().getOrientation()!=a2.getMarqueur1().getOrientation())
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

template<typename TypeValeur>
bool operator< (const Adjacence<TypeValeur>& a1, const Adjacence<TypeValeur>& a2){
	
	if (a1 == a2){
		return false;
	}
	else if(a1.getMarqueur1().getValeur() < a2.getMarqueur1().getValeur()){
		return true;
	}
	else if(a1.getMarqueur1().getValeur() > a2.getMarqueur1().getValeur()){
		return false;
	}
	else{
		if(a1.getMarqueur2().getValeur() < a2.getMarqueur2().getValeur()){
			return true;
		}
		else if(a1.getMarqueur2().getValeur() > a2.getMarqueur2().getValeur()){
			return false;
		}
		else if(a1.getMarqueur1().getOrientation() > a2.getMarqueur1().getOrientation()){
			return true;
		}
		else if(a1.getMarqueur1().getOrientation() < a2.getMarqueur1().getOrientation()){
			return false;
		}
		else return (a1.getMarqueur2().getOrientation() > a2.getMarqueur2().getOrientation());
	}
}
