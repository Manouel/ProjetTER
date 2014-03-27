/*========================================================================
Nom: marqueur.h           auteur: Geoffrey DUMAS
Maj:  27/03/2014         Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Marqueur.
Un marqueur est un objet composé d'une valeur et d'une orientation.
=========================================================================*/
#ifndef MARQUEUR_H
#define MARQUEUR_H

#include<iostream>

template<typename TypeValeur>
class Marqueur
{
  private:
	  TypeValeur valeur; //Valeur du Marqueur
	  char orientation; //orientation du Marqueur
	  
  public:
	  Marqueur(); //Constructeur vide
	  Marqueur(TypeValeur val);
	  Marqueur(TypeValeur val, char ori);
	  Marqueur(const Marqueur& nvT); //Constructeur par recopie
	  virtual ~Marqueur();
	
	  virtual TypeValeur getValeur()const;
	  virtual char getOrientation()const;
	
	  virtual void setValeur(TypeValeur val);
	  virtual void setOrientation(char ori);
	  
	  /*
	  	@param istream& is flot d'entrée
	  	@action lit dans le flot d'entrée l'orientation suivie de la valeur d'un Marqueur
	  */
	  virtual void saisie(std::istream& is); 
	  
	  /*
	  	@param ostream os flot de sortie
	  	@action affiche dans la sortie standard un Marqueur
	  */
	  virtual void affiche(std::ostream& os)const;
};


/*
	@param Marqueur m1 
	@param Marqueur m2
	@return vrai ssi le marqueur m1 est égal au marqueur m2 
		exemple : 	 +1 == +1 // +1 != -1
*/
template<typename TypeValeur>
bool operator== (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2);

/*
	@param Marqueur m1 
	@param Marqueur m2
	@return vrai ssi le marqueur m1 est inférieur au marqueur m2.
		On compare les valeurs, si elles sont égales on compare les signes.
*/
template<typename TypeValeur>
bool operator< (const Marqueur<TypeValeur>& m1, const Marqueur<TypeValeur>& m2);

#endif
