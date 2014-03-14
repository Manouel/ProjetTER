/*========================================================================
Nom: marqueur.cpp           auteur: Geoffrey DUMAS
Maj:  13/02/2014         Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient classe Marqueur.
Un marqueur est un objet composé d'une valeur et d'une orientation 
appartenant à une sequence de gène.
=========================================================================*/
#ifndef MARQUEUR_H
#define MARQUEUR_H

#include<iostream>

template<typename TypeValeur>
class Marqueur
{
  private:
	  TypeValeur valeur;
	  char orientation;
	  
  public:
	  Marqueur(); //Constructeur vide
	  Marqueur(TypeValeur val);
	  Marqueur(TypeValeur val, char ori);
	  Marqueur(const Marqueur& nvT); //Constructeur par recopie
	  virtual ~Marqueur();
	
	  TypeValeur getValeur()const;
	  char getOrientation()const;
	
	  void setValeur(TypeValeur val);
	  void setOrientation(char ori);
	  
	  void saisie(std::istream& is); //Fonction pour saisir un Marqueur
	  void affiche(std::ostream& os)const; //Fonction d'affichage d'un Marqueur
};


/*
@param Marqueur m1 
@param Marqueur m2
@return vrai ssi le marqueur m1 est égal au marqueur m2 
	exemple : 	 +1 == +1 // +1 != -1
*/
template<typename TypeValeur>
bool operator== (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2);

template<typename TypeValeur>
bool operator< (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2);

#endif
