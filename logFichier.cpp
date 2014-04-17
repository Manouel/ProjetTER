/*========================================================================
Nom: log.cpp           auteur: Morgane Vidal
Maj:  27/03/2014         Creation: 13/02/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation des fonctions de la classe Log.
=========================================================================*/

#include "logFichier.h"
#include "exceptionFichier.h"

#include<iostream>
#include<string>
using namespace std;

 		LogFichier::LogFichier(){}
		LogFichier::~LogFichier(){}

void LogFichier::open(const string& nomFichier, const string& typeEntree1, const string& entree1, const string& typeEntree2, const string& entree2, const string& nomAlgo){
	
	fichier.open(nomFichier.c_str(),ios::out|ios::app);
	if(!fichier){
			throw ExceptionFichier("Erreur lors de l'ouverture du fichier !");
		}
		
	fichier<<"========================================================================"<<endl;
	//Affichage des noms de fichier
		if(typeEntree1 == "f"){
			fichier<<"Sequence 1 : "<<entree1<<endl;
			if(typeEntree2 == "f"){
				fichier<<"Sequence 2 : "<<entree2<<endl;
			}
		}
		else {
			if(typeEntree2 == "f"){
				fichier<<"Sequence 1 : "<<entree2<<endl;
			}
		}
		this->ecrireDate();
		
	fichier<<"========================================================================"<<endl;
}

void LogFichier::ecrireDate(){
	
	struct tm date;
	time_t maintenant;
	time(&maintenant);
	date=*localtime(&maintenant);
	fichier<<"Date : "<<date.tm_mday<<"/"<<date.tm_mon+1<<"/"<<date.tm_year+1900<<" "<<date.tm_hour<<":"<<date.tm_min<<endl;

}

void LogFichier::close(){
	fichier.close();
}

void LogFichier::ecrireMatrice(const Alignement& a){
	a.affiche(fichier);
}
