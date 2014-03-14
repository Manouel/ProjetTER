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

template<typename TypeValeur>
Sequence<TypeValeur>::Sequence(){
	ajoutSousSeq();
}

template<typename TypeValeur>
Sequence<TypeValeur>::Sequence(const string& nomFichier, char delim){
	ajoutSousSeq();
	load(nomFichier, delim);
}

template<typename TypeValeur>
Sequence<TypeValeur>::~Sequence() {}

template<typename TypeValeur>
vector<vector<Marqueur<TypeValeur> > > Sequence<TypeValeur>::getSequence() const{
	return this->sequence;
}

template<typename TypeValeur>
Marqueur<TypeValeur> Sequence<TypeValeur>::getElement(int i, int j) const{
	return this->sequence[i][j];
}

template<typename TypeValeur>
vector<Marqueur<TypeValeur> > Sequence<TypeValeur>::getVecteur(int i) const{
	return this->sequence[i];
}

template<typename TypeValeur>
int Sequence<TypeValeur>::nbSousSeq() const{
	return this->sequence.size();
}

template<typename TypeValeur>
void Sequence<TypeValeur>::ajoutElement(Marqueur<TypeValeur>& m){
	this->sequence[this->nbSousSeq()-1].push_back(m);
}

template<typename TypeValeur>
void Sequence<TypeValeur>::ajoutSousSeq(){
	this->sequence.push_back(vector<Marqueur<TypeValeur> >());
}

template<typename TypeValeur>
void Sequence<TypeValeur>::affichage() const{
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

template<typename TypeValeur>
void Sequence<TypeValeur>::load(const string& nomFichier, char delim){
	ifstream fichier(nomFichier.c_str());
	if (!fichier)
	{
		cout << "Erreur ouverture fichier.\n" << endl;
	}
	
	char ori;
	TypeValeur val;
	
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
			Marqueur<TypeValeur> m(val, ori);
			
			this->ajoutElement(m);			
		}
	}
	
	fichier.close();
}

template<typename TypeValeur>
void Sequence<TypeValeur>::save(const string& nomFichier,char delim)
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

template<typename TypeValeur>
vector<Adjacence<TypeValeur> > Sequence<TypeValeur>::listeAdjacence() const{
	vector<Adjacence<TypeValeur> > liste;
	for(int i=0; i<this->nbSousSeq(); i++){
		int tailleSousSeq = this->getVecteur(i).size();
		for(int j=0; j<tailleSousSeq-1;j++){
			Adjacence<TypeValeur> a(this->getElement(i,j),this->getElement(i,j+1));
			liste.push_back(a);
		}
	}
	return liste;
}

template<typename TypeValeur>
int Sequence<TypeValeur>::alignementGlobal(const vector<Marqueur<TypeValeur> >& sequBis, int sub, int indel, int match) const
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

template<typename TypeValeur>
int Sequence<TypeValeur>::breakpoints(Sequence<TypeValeur>& s) const{
	
	vector<Adjacence<TypeValeur> > liste1 = this->listeAdjacence(); 
	vector<Adjacence<TypeValeur> > liste2 = s.listeAdjacence();
	
	sort(liste1.begin(),liste1.begin()+liste1.size()); //Tri des adjacences de la liste de this par ordre de valeur croissante pour la fonction set_difference
	sort(liste2.begin(),liste2.begin()+liste2.size()); //Tri des adjacences de la liste de s par ordre de valeur croissante pour la fonction set_difference
	
	vector<Adjacence<TypeValeur> > diff(liste1.size()+liste2.size()); //Création du tableau des différences entre liste1 et liste2. Sa taille est égale à celle de liste1 ajoutée à celle de liste 2
	typename vector<Adjacence<TypeValeur> >::iterator it; //Itérateur sur la dernière différence retenue
	
	it = set_difference(liste1.begin(), liste1.begin()+liste1.size(),liste2.begin(),liste2.begin()+liste2.size(),diff.begin()); //Execution de la différence entre les deux listes, stockage des différences dans diff et stockage du nombre d'adjacences différentes dans it
	diff.resize(it-diff.begin()); //Modification de la taille de diff pour que celle ci soit égale au nombre de différences stockées
	
	return diff.size(); //Nombre de différences retourné
}

/*
template<typename TypeValeur>
void Sequence<TypeValeur>::preproscessing(vector<Marqueur<TypeValeur>*>& s1, Sequence& s2, 
		map<Marqueur<TypeValeur>,vector<int> >& pos, int num[][]) const
{

}*/

template<typename TypeValeur>
int Sequence<TypeValeur>::intervallesCommuns(Sequence<TypeValeur>& s2) const
{
	vector<Marqueur<TypeValeur>*> s1;

	for(int i=0; i<this->nbSousSeq(); i++){
		for(int j=0; j< s2.getVecteur(i).size(); j++){
			s1.push_back(&s2.sequence[i][j]);
		}
		s1.push_back(NULL);
	}
	
	map<Marqueur<TypeValeur>,vector<int> > pos;
	int num[s1.size()][s1.size()];
	
	
	// Remplissage de pos : parcours de s1 et ajout des positions pour chaque marqueur
	for(int i=0; i< s1.size();i++){
		if(s1[i] != NULL){
			pos[*s1[i]].push_back(i);
		}
	}
	
	// Remplissage de num : calcul du nombre de marqueurs différents entre chaque indices de s1
	for(int i=0; i<s1.size();i++){
		for(int j=0; j<s1.size();j++){
			if(i == j){					// Entre l'indice i et i, 1 marqueur donc 1 différence
				num[i][j] = 1;
			}
			else if (j<i){				// Partie vide de la matrice (j,i -> i,j)
				num[i][j] = 0;
			}
			else{						// Calcul du nombre de marqueurs différents entre i et j
				vector<Marqueur<TypeValeur> > present;			// Liste des marqueurs différents présents de i à j
				
				// Parcours des marqueurs de i à j
				for(int k = i; k<j;k++){
					if(!(find(present.begin(), present.end(), *s1[k]) != present.end())){		// Si le marqueur n'existe pas, on l'ajoute
						present.push_back(*s1[k]);
					}
				}
				
				// On stocke le nombre de marqueurs différents trouvés
				num[i][j]= present.size();
			}
		}
	}
	
	//preproscessing(s1, s2, pos, num);
}



