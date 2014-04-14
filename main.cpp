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
#include "marqueur.h"
#include "sequence.h"
#include "adjacence.h"
#include "alignement.h"

using namespace std;


bool log = false;
bool logDetaille=false;
string nomFichier="out.txt";
/**

	f / s fichier/sequence  f / s fichier/sequence  separateur algo [log : ls/ld] [sortie]
	en ligne de commande : obligation de mettre le signe
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
	
	else{
		
		seq1.load(argv[2],separateur);
	
		
	}
	
	if(strcmp(argv[3],"s")==0){
		
		seq2.remplirSequence(argv[4], separateur);
		
	}
	else{
		seq2.load(argv[4], separateur);
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
		
		
		seq1.alignementLocal(seq2, sub, indel, match);
	}
	else if(strcmp(argv[6], "BP") == 0)
	{
		int nbAdjacencesCommunes = seq1.adjacencesCommunes(seq2);
		cout << "Nombre d'adjacences communes : " << nbAdjacencesCommunes << endl;
	}
	else if(strcmp(argv[6], "IC") == 0)
	{
		cout << seq1.intervallesCommuns(seq2) << endl;
	}
	
	return 0;
}


