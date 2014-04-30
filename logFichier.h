/*========================================================================
Nom: log.cpp           auteur: Morgane Vidal
Maj:  17/04/2014         Creation: 17/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Log. 
Cette classe va servir pour les logs des résultats des trois algorithmes
dans le fichier de sortie.
=========================================================================*/

#ifndef LOGFICHIER_H
#define LOGFICHIER_H

#include <fstream>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include "alignement.h"
#include "adjacence.h"
#include "exceptionFichier.h"

class LogFichier
{
	private:
		std::ofstream fichier;
		
		/**
			@action écrit la Date du jour dans le fichier de sortie
		*/
		virtual void ecrireDate();
		

	public:
		
		static bool log;
		static bool logDetaille;
		static std::string nomFichier;
	
		LogFichier() throw(ExceptionFichier);
		virtual ~LogFichier();


		/**
			@param typeEntree1, typeEntree2 type de entree1 ou entree2 (f pour fichier, s pour sequence)
			@param entree1, entree2	fichier ou séquence
			@param seq1, seq2 séquences si les séquences ont été récupérées dans des fichiers
			
			@action ouvre le fichier et y écrit l'entête. Celle-ci est différente si ce sont des logs détaillés ou non.
				L'entête ressemble à : 
				========================================================================
				Date : 17/4/2014 10:29
				Sequence 1 : fichiertest_minimal.csv
				Sequence 2 : fichiertest_minimal.csv
				Algorithme : Intervalles Communs
				========================================================================
		*/
		virtual void ecrireEnTete(const std::string& typeEntree1, const std::string& entree1, const std::string& typeEntree2, const std::string& entree2, const std::string& nomAlgo, const std::string& seq1, const std::string& seq2);
		
		
		/**
			@param indel, match, sub	coûts de comparaison des marqueurs
			@action écrit dans le fichier le résultat de la méthode d'alignement local
		*/
		virtual void afficherCouts(int indel, int match, int sub);
		
		/**
			@param i indice de la sous-séquence
			@param sousSeq sous-séquence à laquelle est lié l'objet a
			@param a objet alignement contenant la matrice résultat
			@param indel cout permettant de déterminer s'il s'agit de score ou distance
			@action écrit dans le fichier le résultat de la méthode d'alignement local sur une sous séquence de s
		*/
		virtual void ecrireResultatAlignement(int i, const std::string& sousSeq, const Alignement& a, const int indel);
		
		/**
			@param i indice de la sous-séquence
			@param sousSeq sous-séquence comparée avec s1
			@param inter liste des adjacences communes retournée par l'algo
			@param scoreAbsolu score absolu calculé
			@param scoreRelatif score relatif calculé
			@action écrit dans le fichier la liste des adjacences communes calculée
		*/
		virtual void ecrireResultatAdjacencesCommunes(int i, const std::string& sousSeq, std::vector<std::string> inter,
														int scoreAbsolu, float scoreRelatif);
		
		/**
			@param i indice de la sous-séquence
			@param sousSeq sous-séquence comparée avec s1
		*/
		virtual void ecrireSousSequence(int i, const std::string& sousSeq);
		
		/**
			@param a, b bornes de l'intervalle commun dans s1
			@param c, d bornes de l'intervalle commun dans s2
			@action écrit dans le fichier les bornes de l'intervalle commun trouvé
		*/
		virtual void affichierIntervallesCommuns(int a, int b, int c, int d);
		
		/**
			@param nbIntervalles Nombre d'intervalles communs trouvés dans une sous-séquence
		*/
		virtual void resultatSousSeq(int nbIntervalles);
		
		/**
			@param nbTotalIntervalles Nombre d'intervalles communs trouvés dans une séquence
		*/
		virtual void resultatSeq(int nbTotalIntervalles);
};


#endif
