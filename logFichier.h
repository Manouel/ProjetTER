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

#include<fstream>
#include<iostream>
#include <time.h>
#include <string>
#include "alignement.h"


class LogFichier
{
	
	private:
		std::ofstream fichier;
		virtual void ecrireDate();

	public:
		
		int log;
		int logDetaille;
	
		LogFichier();
		virtual ~LogFichier();


		/**
			@param nomFichier nom du fichier à ouvrir
			@param typeEntree1, typeEntree2 type de entree1 ou entree2 (f pour fichier, s pour sequence)
			@param entree1, entree2	fichier ou séquence
			
			@action ouvre le fichier et y écrit l'entête. Celle-ci est différente si ce sont des logs détaillés ou non.
				L'entête ressemble à : 
				========================================================================
				Date : 17/4/2014 10:29
				Sequence 1 : fichiertest_minimal.csv
				Sequence 2 : fichiertest_minimal.csv
				Algorithme : Intervalles Communs
				========================================================================
		*/
		virtual void open(const std::string& nomFichier, const std::string& typeEntree1, const std::string& entree1, const std::string& typeEntree2, const std::string& entree2, const std::string& nomAlgo);
		virtual void close();
		
		virtual void ecrireMatrice(const Alignement& a);
		
};


#endif
