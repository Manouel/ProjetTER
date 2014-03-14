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

using namespace std;


bool log = false;


int main(int argc, char *argv[])
{
	if (argc != 4 && argc != 5)
	{
		cerr << "Mauvais nombre d'arguments ! (file1 file2 separateur algo [l])" << endl;
	}
	
	char separateur = argv[3][0];
	Sequence<string> seq1(argv[1], separateur);
	Sequence<string> seq2(argv[2], separateur);
	
	if (strcmp(argv[5], "l") == 0)
		log = true;
	
	if (strcmp(argv[4], "AG") == 0)
	{
		int sub, indel, match;
	
		cout << "Veuillez entrer le cout de substitution de l'alignement global : ";
		cin >> sub;
		cout << "Veuillez entrer le cout d'insertion et de délétion de l'alignement global : ";
		cin >> indel;
		cout << "Veuillez entrer le cout de correspondance de l'alignement global : ";
		cin >> match;
		
		
		int val = seq1.alignementGlobal(seq2.getVecteur(0), sub, indel, match);
		if (indel < 0)
			cout << "Score alignement global : " << val << endl;
		else
			cout << "Distance alignement global : " << val << endl;
		
	}
	else if(strcmp(argv[4], "BP") == 0)
	{
		int nbBreakpoints = seq1.breakpoints(seq2);
		cout << "Nombre de breakpoints : " << nbBreakpoints << endl;
	}
	else if(strcmp(argv[4], "IC") == 0)
	{
		;
	}
	

	return 0;
}
