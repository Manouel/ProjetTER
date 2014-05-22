/*========================================================================
Nom: log.cpp           auteur: Morgane Vidal
Maj:  22/05/2014         Creation: 13/02/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation des fonctions de la classe Log.
=========================================================================*/

#include "logFichier.h"

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

bool LogFichier::log = false;
bool LogFichier::logDetaille = false;
string LogFichier::nomFichier = "out.txt";

LogFichier::LogFichier() throw(ExceptionFichier)
{
	if(log)
	{
		fichier.open(nomFichier.c_str(), ios::out | ios::app);
		if(!fichier)
		{
			throw ExceptionFichier("Erreur lors de l'ouverture du fichier " + nomFichier + " !");
		}
	}
}

LogFichier::~LogFichier()
{
	fichier.close();
}

void LogFichier::ecrireEnTete(const string& typeEntree1, const string& entree1, const string& typeEntree2, const string& entree2, 									const string& nomAlgo, const string& seq1, const string& seq2)
{
	fichier << "========================================================================" << endl;

	ecrireDate();
	
	//Affichage des noms de fichiers et des séquences si on est en log détaillés.
	if(logDetaille)
	{				
		if(typeEntree1 == "s")
		{
			fichier << "Sequence 1 : " << seq1 << endl;
		}
		else if(typeEntree1 == "f") 
		{
			fichier << "Fichier 1 : " << entree1 << endl;
			fichier << "Sequence 1 : " << seq1 << endl;
		}
		
			
		if(typeEntree2 == "s")
		{
			fichier << "Sequence 2 : " << seq2 << endl;
		}
		else if(typeEntree2 == "f") 
		{
			fichier << "Fichier 2 : " << entree2 << endl;
			fichier << "Sequence 2 : " << seq2 << endl;
		}
	}

	if(nomAlgo.compare("AL") == 0)
	{
		fichier << "Algorithme d'alignement local" << endl;
	}
	else if(nomAlgo.compare("IC") == 0)
	{
		fichier << "Algorithme d'intervalles communs" << endl;
	}
	else if(nomAlgo.compare("AC") == 0)
	{
		fichier << "Algorithme d'adjacences communes" << endl;
	}
		
	fichier << "========================================================================" << endl;
}

void LogFichier::ecrireDate()
{
	struct tm date;
	time_t maintenant;
	time(&maintenant);
	date = *localtime(&maintenant);
	fichier << "Date : " << date.tm_mday << "/" << date.tm_mon+1 << "/" << date.tm_year+1900 << " " << date.tm_hour << ":" 
			<< date.tm_min << endl;
}

void LogFichier::ecrireResultatAlignement(int i, const string& sousSeq, const Alignement& a, const int indel)
{
	if(logDetaille)
	{
		ecrireSousSequence(i, sousSeq);
		a.affiche(fichier);
	}
	
	if(indel < 0)
	{
		fichier << "\tScore alignement local : " << a.getResultat() << endl << endl;
	}
	else
	{ 
		fichier << "\tDistance alignement local : " << a.getResultat() << endl << endl;
	}
}

void LogFichier::ecrireResultatAdjacencesCommunes(int i, const string& sousSeq, vector<string> inter, int scoreAbsolu, float scoreRelatif)
{
	if(logDetaille)
	{
		ecrireSousSequence(i, sousSeq);
	}
		
	vector<string>::iterator it;
	for(it = inter.begin(); it != inter.end(); it++)
	{
			fichier << "\t\t" << *it << endl;
	}
	
	fichier << endl << "\tScore absolu : " << scoreAbsolu << endl;
	fichier << "\tScore relatif : " << scoreRelatif << endl << endl;	
}

void LogFichier::ecrireSousSequence(int i, const std::string& sousSeq)
{
	if(logDetaille)
	{
		fichier << "Sequence 2." << i+1 << " : " << sousSeq << endl;
	}s
}

void LogFichier::afficherIntervallesCommuns(int a, int b, int c, int d)
{

	fichier << "\t(" << a << " - " << b << ") - (" << c << " - " << d << ")" << endl;
}

void LogFichier::resultatSousSeq(int nbIntervalles)
{
	fichier << "Nombre d'intervalles communs : " << nbIntervalles << endl << endl;
}

void LogFichier::resultatSeq(int nbTotalIntervalles)
{
	fichier << "Nombre total d'intervalles communs : " << nbTotalIntervalles << endl;
}

void LogFichier::afficherCouts(int indel, int match, int sub)
{
	fichier << "Coût substitution : " << sub << endl;
	fichier << "Coût insertion/deletion : " << indel << endl;
	fichier << "Coût de correspondance : " << match << endl << endl;	
}
