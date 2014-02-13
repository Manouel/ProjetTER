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

class Adjacence{

private:
	Marqueur marqueur1;
	Marqueur marqueur2;

public:
	Adjacence(Marqueur m1, Marqueur m2);
	Marqueur getMarqueur1() const;
	Marqueur getMarqueur2() const;
	
};

/*
@param Adjacence a1 
@param Adjacence a2
@return vrai ssi les marqueurs de a1 sont égaux aux marqueurs de a2 ou à l'inverse des marqueurs de a2 
	exemple : ( +1 +2 ) == ( +1 +2 )
	   	  ( +1 +2 ) == ( -2 -1 ) 
*/
bool operator== (const Adjacence& a1, const Adjacence& a2);

#endif
