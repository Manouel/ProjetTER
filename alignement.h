/*========================================================================
Nom: alignement.h           auteur: Manuel CHATAIGNER
Maj:  27/03/2014         Creation: 17/03/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Alignement.
Un Alignement est le résultat de l'algorithme d'alignement local. Il est 
composé d'une matrice correspondant à la matrice de résultat de l'algorithme 
d'alignement global, du nombre de lignes et du nombre de colonnes.
=========================================================================*/

#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H
#include<iostream>
class Alignement{
	private:
		int** mat; //matrice résultat de l'algorithme d'alignement local
		int lignes; //nombre de lignes de la matrice
		int colonnes; //nombre de colonnes de la matrice
	
	public:
		Alignement(int lignes, int colonnes);
		Alignement(const Alignement& a);
		virtual ~Alignement();
		
		virtual int getElement(int i,int j) const;
		virtual int getResultat() const;
		virtual void setElement(int i, int j, int val);
		virtual void affiche(std::ostream& os)const;
};



#endif
