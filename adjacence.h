/*========================================================================
Nom: adjacence.h           auteur: Morgane Vidal
Maj:  22/05/2014           Creation: 13/02/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Adjacence. 
Cette classe représente une adjacence de deux Marqueurs présents dans une 
sous-séquence.
=========================================================================*/

#ifndef ADJACENCE_H
#define ADJACENCE_H

#include "marqueur.h"

template<typename TypeValeur>
class Adjacence
{
	private:
		// Les attributs sont les deux marqueurs adjacents
		Marqueur<TypeValeur> marqueur1; 
		Marqueur<TypeValeur> marqueur2;

	public:
		Adjacence();
		Adjacence(Marqueur<TypeValeur> m1, Marqueur<TypeValeur> m2);
		virtual ~Adjacence();
	
		virtual Marqueur<TypeValeur> getMarqueur1() const;
		virtual Marqueur<TypeValeur> getMarqueur2() const;
	
		/**
			@return chaine de caractère contenant les deux marqueurs de l'adjacence
		*/
		virtual std::string toString() const;
	
		/**
		  	@param ostream os flot de sortie
		  	@action affiche dans la sortie standard une Adjacence
		*/
		virtual void affiche() const;
	
};

/**
	@param Adjacence a1 
	@param Adjacence a2
	@return vrai ssi les marqueurs de a1 sont égaux aux marqueurs de a2 ou à l'inverse des marqueurs de a2 
		exemple : ( +1 +2 ) == ( +1 +2 )
		   	  ( +1 +2 ) == ( -2 -1 ) 
*/
template<typename TypeValeur>
bool operator== (const Adjacence<TypeValeur>& a1, const Adjacence<TypeValeur>& a2);

/**
	@param Adjacence a1
	@param Adjacence a2
	@return vrai ssi a1<a2. On compare les valeurs des attributs marqueur1 de chaque adjacene,
		en cas d'égalité, on compare celles des attributs marqueur2 puis on compare les signes 
		des marqueurs 1 et enfin ceux des marqueurs 2.
*/
template<typename TypeValeur>
bool operator< (const Adjacence<TypeValeur>& a1, const Adjacence<TypeValeur>& a2);

#endif
