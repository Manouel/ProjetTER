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
#include "adjacence.h"


class Sequence{
	private:
		std::vector<std::vector<Marqueur> > sequence;
	public:
		
		Sequence();
		Sequence(const std::string& nomFichier, char delim);
		//Sequence(const Sequence& sequ);
		virtual ~Sequence();
		
		std::vector<std::vector<Marqueur> > getSequence() const;
		Marqueur getElement(int i, int j) const;
		std::vector<Marqueur> getVecteur(int i) const;
		
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
		void load(const std::string& nomFichier, char delim);
		
		/**
		  @action Ecris le contenu d'une Séquence dans le fichier
		  @param Nom du fichier à écrire 
		  @param Délimiteur indiquant le changement de sous-séquences 
		*/
		void save(const std::string& nomFichier,char delim);
		
		void affichage() const;
		
		std::vector<Adjacence> listeAdjacence() const;
		
		/* Algo alignement global */
		
		/**
		 @param sequBis sequence à comparer avec this
		 @param sub, inser, delet, match valeur des couts des opérations
		 @return score
		*/
		int alignementGlobal(const std::vector<Marqueur>& sequBis, int sub, int indel, int match) const;
		
		int breakpoints(Sequence& s) const;
};


#endif
