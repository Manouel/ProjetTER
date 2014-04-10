/*========================================================================
Nom: sequence.h           auteur: Jonathan Dufetel
Maj:  27/03/2014           Creation: 27/01/2014
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
#include <map>
#include "marqueur.h"
#include "adjacence.h"
#include "alignement.h"

template<typename TypeValeur>
class Sequence{
	private:
		std::vector<std::vector<Marqueur<TypeValeur> > > sequence;
		
		/**
		 @action Remplissage de pos et num
		 @param s1 Liste de pointeurs vers les marqueurs de la sequence this
		 @param s2 Sequence à comparer
		 @param pos Tableau des positions de chaque marqueur dans s1
		 @param num Matrice des différences entre 2 marqueurs dans s1
		*/
		/*void preproscessing(std::vector<Marqueur<TypeValeur>*>& s1, Sequence& s2, 
				std::map<Marqueur<TypeValeur>,std::vector<int> >& pos, int num[][]) const;*/
				
		/**
		 @return Liste des adjacences de la séquence
		*/
		virtual std::vector<Adjacence<TypeValeur> > listeAdjacence() const;
		
		/**
		 @param Indice de la sous-séquence
		 @return Liste des adjacences de la sous-séquence i
		*/
		virtual std::vector<Adjacence<TypeValeur> > listeAdjacence(int i) const;
		
		
		/**
		 @action Applique l'algorithme d'alignement local entre la première sous-séquence de this 
		 		 et la sous-séquence s, puis retourne le score obtenu
		 @param s sous-séquence à comparer avec this
		 @param sub, inser, delet, match valeur des couts des opérations
		 @return un objet alignement contenant la matrice finale
		*/
		virtual Alignement calculAlignement(const std::vector<Marqueur<TypeValeur> >& s, int sub, int indel, int match) const;
		
	public:
		
		Sequence();
		Sequence(const std::string& nomFichier, char delim);
		//Sequence(const Sequence& sequ);
		virtual ~Sequence();
		
		virtual std::vector<std::vector<Marqueur<TypeValeur> > > getSequence() const;
		virtual Marqueur<TypeValeur> getElement(int i, int j) const;
		virtual std::vector<Marqueur<TypeValeur> > getVecteur(int i) const;
		
		/**
		  @return Nombre de sous-séquences
		*/
		virtual int nbSousSeq() const;
		
		/**
		  @param Marqueur à ajouter en fin de Séquence
		*/
		virtual void ajoutElement(Marqueur<TypeValeur>& t);
		
		/**
		  @action Ajout d'une nouvelle sous-séquence
		*/
		virtual void ajoutSousSeq();
		//virtual void supElement(Marqueur<TypeValeur>& t);
		//virtual bool rechercheElement(const Marqueur<TypeValeur>& t);
		
		/**
		  @action Créé une Séquence à partir du fichier
		  @param Nom du fichier à lire 
		  @param Délimiteur indiquant le changement de sous-séquences 
		*/
		virtual int load(const std::string& nomFichier, char delim);
		
		/**
		  @action Ecris le contenu d'une Séquence dans le fichier
		  @param Nom du fichier à écrire 
		  @param Délimiteur indiquant le changement de sous-séquences 
		*/
		virtual int save(const std::string& nomFichier,char delim);
		
		virtual void affichage(std::ostream& os) const;
		
		
		/* Algo alignement local */
		
		/**
		 @action Appelle la méthode privée du calcul de l'algorithme d'alignement local avec la première sous-séquence de this 
		 		 pour chaque sous-séquence de s
		 @param s séquence à comparer avec this
		 @param sub, inser, delet, match valeur des couts des opérations
		*/
		virtual void alignementLocal(const Sequence<TypeValeur>& s, int sub, int indel, int match) const;
		
		
		/* Algo breakpoints */
		
		/**
		 @action Retourne le nombre d'adjacences différentes entre la séquence this et une séquence s
		 @param s sequence à comparer avec this
		 @return nombre d'adjacences différentes
		*/
		virtual int breakpoints(const Sequence<TypeValeur>& s) const;
		
		
		/* Intervalles communs */
		
		/**
		 @action Retourne le nombre d'intervalles communs entre la séquence this et s2
		 @param s2 sequence à comparer avec this
		 @return nombre d'intervalles communs
		*/
		virtual int intervallesCommuns(const Sequence<TypeValeur>& s) const;
		
};


#endif
