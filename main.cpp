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


bool log = false;
bool logDetaille=false;
string nomFichier="out.txt";
/**

	f / s fichier/sequence  f / s fichier/sequence  separateur algo [log : ls/ld] [sortie]
	exemple : s "+10 +3 +5" f monfichier.txt '&' AC ls sortie.txt 
*/

int main(int argc, char *argv[])
{
	LogFichier l;
	l.open("","","","","","");
	
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
	
	else{
		
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
	else{
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
		log = true;
		if(argc==9){
			nomFichier=argv[8];
		}
		if(strcmp(argv[7], "ld") == 0 ){
			logDetaille=true;
		}
		ofstream fichier;
		fichier.open(nomFichier.c_str(),ios::out|ios::app); //On ouvre le fichiers et on place le curseur à la fin pour ne pas écrire par dessus d'autres données du fichier de sortie.
		if(!fichier){
			throw ExceptionFichier("Erreur lors de l'ouverture du fichier "+nomFichier+" !");
		}
		fichier<<"========================================================================"<<endl;
		//Affichage de la date du jour
		struct tm date;
		time_t maintenant;
		time(&maintenant);
		date=*localtime(&maintenant);
		fichier<<"Date : "<<date.tm_mday<<"/"<<date.tm_mon+1<<"/"<<date.tm_year+1900<<" "<<date.tm_hour<<":"<<date.tm_min<<endl;
		
		//Affichage des noms de fichier
		if(strcmp(argv[1],"f")==0){
			fichier<<"Sequence 1 : "<<argv[2]<<endl;
			if(strcmp(argv[3],"f")==0){
				fichier<<"Sequence 2 : "<<argv[4]<<endl;
			}
		}
		else {
			if(strcmp(argv[3],"f")==0){
				fichier<<"Sequence 1 : "<<argv[4]<<endl;
			}
		}
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
			cout << "Nombre d'adjacences communes : " << nbAdjacencesCommunes << endl;
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


