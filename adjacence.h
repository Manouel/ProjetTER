/*========================================================================
Nom: adjacence.h           auteur: Morgane Vidal
Maj:  13/02/2014           Creation: 13/02/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Adjacence. 
Classe représentant une adjacence de deux Marqueurs présente dans une 
sous-séquence de marqueurs.
=========================================================================*/

#ifndef ADJACENCE_H
#define ADJACENCE_H
#include "marqueur.h"

template<typename TypeValeur>
class Adjacence{

private:
	Marqueur<TypeValeur> marqueur1;
	Marqueur<TypeValeur> marqueur2;

public:
	Adjacence();
	Adjacence(Marqueur<TypeValeur> m1, Marqueur<TypeValeur> m2);
	virtual ~Adjacence();
	Marqueur<TypeValeur> getMarqueur1() const;
	Marqueur<TypeValeur> getMarqueur2() const;
	void affiche() const;
	
};

/*
@param Adjacence a1 
@param Adjacence a2
@return vrai ssi les marqueurs de a1 sont égaux aux marqueurs de a2 ou à l'inverse des marqueurs de a2 
	exemple : ( +1 +2 ) == ( +1 +2 )
	   	  ( +1 +2 ) == ( -2 -1 ) 
*/
template<typename TypeValeur>
bool operator== (const Adjacence<TypeValeur>& a1, const Adjacence<TypeValeur>& a2);

template<typename TypeValeur>
bool operator< (const Adjacence<TypeValeur>& a1, const Adjacence<TypeValeur>& a2);

#endif
