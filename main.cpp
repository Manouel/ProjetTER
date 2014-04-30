/*========================================================================
Nom: main.cpp           auteur: Manuel Chataigner
Maj:  14/03/2014           Creation: 14/03/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient le main du projet et l'appel aux différents 
algorithmes de comparaison.
=========================================================================*/

#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include "marqueur.h"
#include "sequence.h"
#include "adjacence.h"
#include "alignement.h"
#include "exceptionFichier.h"
#include "logFichier.h"
#include <fstream>

using namespace std;

/**

	f / s fichier/sequence  f / s fichier/sequence  separateur algo [log : ls/ld] [sortie]
	exemple : s "+10 +3 +5" f monfichier.txt '&' AC ls sortie.txt 
*/

int main(int argc, char *argv[])
{
	if (argc < 7 || argc>9)
	{
		cerr << "Mauvais nombre d'arguments ! ( type file/seq type file/seq separateur algo [ls/ld] [nomfichier])" << endl;
	}
	
	char separateur = argv[5][0];
	
	Sequence<string> seq1;
	Sequence<string> seq2;
	
	if(strcmp(argv[1],"s")==0){
		seq1.remplirSequence(argv[2], separateur);
	}
	
	else if (strcmp(argv[1],"f")==0){
		
		try{
			seq1.load(argv[2],separateur);
		}
		catch(ExceptionFichier e){
			cerr<<"ERREUR Sequence 1 : "<<e.verdict()<<endl;
			return 0;
		}
		
	}
	
	if(strcmp(argv[3],"s")==0){

		seq2.remplirSequence(argv[4], separateur);
		
	}
	else if(strcmp(argv[3],"f")==0){
		try{
			seq2.load(argv[4],separateur);
		}
		catch(ExceptionFichier e){
			cerr<<"ERREUR Sequence 2 : "<<e.verdict()<<endl;
			return 0;
		}
	}
	
	if (argc >= 8  && (strcmp(argv[7], "ls") == 0 ||strcmp(argv[7], "ld") == 0))
	{
		LogFichier::log = true;
		if(argc==9){
			LogFichier::nomFichier=argv[8];
		}
		if(strcmp(argv[7], "ld") == 0 ){
			LogFichier::logDetaille=true;
		}
	}
	
	if(LogFichier::log){
		LogFichier l;
		l.ecrireEnTete(argv[1], argv[2], argv[3], argv[4], argv[6], seq1.toString(), seq2.toString());
	}
	
	
	if (strcmp(argv[6], "AL") == 0)
	{
		int sub, indel, match;
	
		cout << "Veuillez entrer le cout de substitution de l'alignement local : ";
		cin >> sub;
		cout << "Veuillez entrer le cout d'insertion et de délétion de l'alignement local : ";
		cin >> indel;
		cout << "Veuillez entrer le cout de correspondance de l'alignement local : ";
		cin >> match;
		

		try{
			seq1.alignementLocal(seq2, sub, indel, match);
		}
		catch(ExceptionFichier e){
			cerr<<"ERREUR Fichier log Alignement Local : "<<e.verdict()<<endl;
			return 0;
		}
	}
	else if(strcmp(argv[6], "AC") == 0)
	{
		try{
			int nbAdjacencesCommunes = seq1.adjacencesCommunes(seq2);
		}
		catch(ExceptionFichier e){
			cerr<<"ERREUR Fichier log Adjacences communes : "<<e.verdict()<<endl;
			return 0;
		}
	}
	else if(strcmp(argv[6], "IC") == 0)
	{
		try{
			cout << seq1.intervallesCommuns(seq2) << endl;
		}
		catch(ExceptionFichier e){
			cerr<<"ERREUR Fichier log Intervalles Communs : "<<e.verdict()<<endl;
			return 0;
		}
	}
	
	return 0;
}


