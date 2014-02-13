/*========================================================================
Nom: sequence.h           auteur: Jonathan Dufetel
Maj:  13/02/2014           Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Sequence. 
Classe représentant une séquence de gènes et composée d'une liste de
sous-séquences de marqueurs.
=========================================================================*/

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <string> 
#include "marqueur.h"

using namespace std;


class Sequence{
	private:
		vector<vector<Marqueur> > sequence;
	public:
		
		Sequence();
		Sequence(const string& nomFichier, char delim);
		//Sequence(const Sequence& sequ);
		
		vector<vector<Marqueur> > getSequence() const;
		Marqueur getElement(int i, int j) const;
		vector<Marqueur> getVecteur(int i) const;
		
		/**
		  @return Nombre de sous-séquences
		*/
		int nbSousSeq() const;
		
		/**
		  @param Marqueur à ajouter en fin de Séquence
		*/
		void ajoutElement(Marqueur& t);
		
		/**
		  @action Ajout d'une nouvelle sous-séquence
		*/
		void ajoutSousSeq();
		void supElement(Marqueur& t);
		bool rechercheElement(const Marqueur& t);
		
		/**
      @action Créé une Séquence à partir du fichier
      @param Nom du fichier à lire 
      @param Délimiteur indiquant le changement de sous-séquences 
    */
		void load(const string& nomFichier, char delim);
		
		/**
      @action Ecris le contenu d'une Séquence dans le fichier
      @param Nom du fichier à écrire 
      @param Délimiteur indiquant le changement de sous-séquences 
    */
		void save(const string& nomFichier,char delim);
		
		void affichage() const;
		
		
		/* Algo alignement global */
		
		/**
		 @param sequBis sequence à comparer avec this
		 @param sub, inser, delet, match valeur des couts des opérations
		 @return score
		*/
		int alignementGlobal(const vector<Marqueur>& sequBis, int sub, int indel, int match) const;
};


#endif
