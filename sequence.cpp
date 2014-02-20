/*========================================================================
Nom: sequence.cpp           auteur: Jonathan Dufetel
Maj:  13/02/2014           Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Adjacence. 
Ce fichier contient l'implémentation des fonctions de la classe Sequence.
=========================================================================*/

#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "sequence.h"
#include "adjacence.h"

using namespace std;

Sequence::Sequence(){
	ajoutSousSeq();
}

Sequence::Sequence(const string& nomFichier, char delim){
	ajoutSousSeq();
	load(nomFichier, delim);
}

Sequence::~Sequence() {}


vector<vector<Marqueur> > Sequence::getSequence() const{
	return this->sequence;
}

Marqueur Sequence::getElement(int i, int j) const{
	return this->sequence[i][j];
}

vector<Marqueur> Sequence::getVecteur(int i) const{
	return this->sequence[i];
}

int Sequence::nbSousSeq() const{
	return this->sequence.size();
}

void Sequence::ajoutElement(Marqueur& m){
	this->sequence[this->nbSousSeq()-1].push_back(m);
}

void Sequence::ajoutSousSeq(){
	this->sequence.push_back(vector<Marqueur>());
}

void Sequence::affichage() const{
	for(int i=0;i<nbSousSeq();i++)
	{
		for(int j=0;j<this->getVecteur(i).size();j++)
		{
			cout<< getElement(i,j).getOrientation() << getElement(i,j).getValeur()<<" ";
		}
		cout<<"\t";
	}
	cout<<endl;
}

void Sequence::load(const string& nomFichier, char delim){
	ifstream fichier(nomFichier.c_str());
	if (!fichier)
	{
		cout << "Erreur ouverture fichier.\n" << endl;
	}
	
	char ori;
	int val;
	
	/* Lecture du signe puis de la valeur du marqueur */
	while (fichier >> ori)
	{
		if (ori == delim)
		{
			this->ajoutSousSeq();
		}
		else
		{
			fichier >> val;
			Marqueur m(val, ori);
			
			this->ajoutElement(m);			
		}
	}
	
	fichier.close();
}

void Sequence::save(const string& nomFichier,char delim)
{
	ofstream fichier(nomFichier.c_str());
	if (!fichier)
	{
		cout << "Erreur ouverture fichier.\n" << endl;
	}
	
	for(int i = 0; i<nbSousSeq(); i++)
	{
		for(int j =0;j<getVecteur(i).size();j++)
		{
			fichier<< getElement(i,j).getOrientation() << getElement(i,j).getValeur() << endl;
			
		}
		if(i!=nbSousSeq()-1)
		fichier << delim << endl; 	
		
	}
	
	fichier.close();
}

vector<Adjacence> Sequence::listeAdjacence() const{
	vector<Adjacence> liste;
	for(int i=0; i<this->nbSousSeq(); i++){
		int tailleSousSeq = this->getVecteur(i).size();
		for(int j=0; j<tailleSousSeq-1;j++){
			Adjacence a(this->getElement(i,j),this->getElement(i,j+1));
			liste.push_back(a);
		}
	}
	return liste;
}

int Sequence::alignementGlobal(const vector<Marqueur>& sequBis, int sub, int indel, int match) const
{
	int gauche; //valeur si on vient de la gauche
	int diag; //valeur si on vient de la diagonale
	int haut; //valeur si on vient du haut
	
	int mat[this->getVecteur(0).size()+1][sequBis.size()+1];

	mat[0][0]=0;
	
	/*Initialisation ligne et colonne 0 :*/
	for(int i=1;i<this->getVecteur(0).size()+1;i++)
	{
		mat[i][0]=mat[i-1][0]+indel;
	}
	for(int j=1;j<sequBis.size()+1;j++)
	{
		mat[0][j]=mat[0][j-1]+indel;
	}
	
	/*Calcul des valeurs de la matrice*/
	for(int i=1;i<this->getVecteur(0).size()+1;i++)
	{
		for(int j=1;j<sequBis.size()+1;j++)
		{
			/*Calcul des 3 valeurs possibles pour mat[i][j]*/
			gauche=mat[i][j-1]+indel;
			haut=mat[i-1][j]+indel;
			
			if(this->getElement(0,i-1).getValeur()==sequBis[j-1].getValeur()) //Modif pour pas prendre en compte orientation dans comparaison
			{
				diag=mat[i-1][j-1]+match;
			}
			else
			{
				diag=mat[i-1][j-1]+sub;
			}
			if(indel<0){
			/*Calcul de la valeur la plus grande pour mettre dans mat[i][j]*/
			if(gauche>haut)
			{
				if(gauche>diag)
				{
					mat[i][j]=gauche;
				}
				else
				{
					mat[i][j]=diag;
				}
			}
			else
			{
				if(haut>diag)
				{
					mat[i][j]=haut;
				}
				else
				{
					mat[i][j]=diag;
				}
			}
			}else
			{
				if(gauche<haut)
			{
				if(gauche<diag)
				{
					mat[i][j]=gauche;
				}
				else
				{
					mat[i][j]=diag;
				}
			}
			else
			{
				if(haut<diag)
				{
					mat[i][j]=haut;
				}
				else
				{
					mat[i][j]=diag;
				}
			}
			}
		}
	}
	
	for(int i=0;i<this->getVecteur(0).size()+1;i++)
	{
		for(int j=0;j<sequBis.size()+1;j++)
		{
			cout<<mat[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<endl;
		
	return mat[this->getVecteur(0).size()][sequBis.size()]; //On retourne la dernière case de la matrice (le score)
}

int Sequence::breakpoints(Sequence& s) const{
	
	vector<Adjacence> liste1 = this->listeAdjacence();
	vector<Adjacence> liste2 = s.listeAdjacence();
	
	sort(liste1.begin(),liste1.begin()+liste1.size());
	sort(liste2.begin(),liste2.begin()+liste2.size());
	
	vector<Adjacence> diff(liste1.size()+liste2.size());
	vector<Adjacence>::iterator it;
	
	it = set_difference(liste1.begin(), liste1.begin()+liste1.size(),liste2.begin(),liste2.begin()+liste2.size(),diff.begin());
	diff.resize(it-diff.begin());
	
	return diff.size();
}
