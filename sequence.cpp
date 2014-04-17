/*========================================================================
Nom: sequence.cpp           auteur: Jonathan Dufetel
Maj:  27/03/2014           Creation: 27/01/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe Adjacence. 
Ce fichier contient l'implémentation des fonctions de la classe Sequence.
=========================================================================*/

#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <time.h>
#include "sequence.h"
#include "adjacence.h"


using namespace std;

template<typename TypeValeur>
Sequence<TypeValeur>::Sequence(){
	ajoutSousSeq();
}

template<typename TypeValeur>
Sequence<TypeValeur>::Sequence(const string& seq, char delim){
	remplirSequence(seq, delim);	
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
void Sequence<TypeValeur>::affichage(ostream& os) const{
	for(int i=0;i<nbSousSeq();i++)
	{
		for(int j=0;j<this->getVecteur(i).size();j++)
		{
			os<< getElement(i,j).getOrientation() << getElement(i,j).getValeur()<<" ";
		}
		os<<"& ";
	}
	
}

template<typename TypeValeur>
void Sequence<TypeValeur>::remplirSequence(const std::string& seq, char delim){
	
	char ori;
	char premierCar;
	TypeValeur val;
	stringstream ss(seq);
	
	while (ss >> premierCar)
	{
		if (premierCar == delim)
		{
			this->ajoutSousSeq();
		
		}
		else
		{
			if(premierCar=='+' || premierCar=='-')
			{
			
				ori=premierCar;
			
			}
			else
			{ //Sinon ça veut dire qu'on va mettre comme orientation + par défaut

				ori='+';
				ss.seekg(-1,ios::cur);
			
			}
			
			ss >> val;
			Marqueur<TypeValeur> m(val, ori);
	
			this->ajoutElement(m);
		}
	}
}

template<typename TypeValeur>
void Sequence<TypeValeur>::load(const string& nomFichier, char delim) throw(ExceptionFichier){
	ifstream fichier(nomFichier.c_str());
	if (!fichier){
		throw ExceptionFichier("Erreur lors de l'ouverture du fichier "+nomFichier+" !");
	}
	
	char premierCar;
	char ori;
	TypeValeur val;
	
	/* Lecture du signe puis de la valeur du marqueur */
	while (fichier >> premierCar)
	{
		if (premierCar == delim)
		{
			this->ajoutSousSeq();
		
		}
		else
		{
			if(premierCar=='+' || premierCar=='-')
			{
			
				ori=premierCar;
			
			}
			else
			{ //Sinon ça veut dire qu'on va mettre comme orientation + par défaut

				ori='+';
				fichier.seekg(-1,ios::cur);
			
			}
			
			fichier >> val;
			Marqueur<TypeValeur> m(val, ori);
	
			this->ajoutElement(m);
		}
	}
	
	fichier.close();
}

template<typename TypeValeur>
void Sequence<TypeValeur>::save(const string& nomFichier,char delim) throw(ExceptionFichier)
{
	ofstream fichier(nomFichier.c_str());
	if (!fichier){
		throw ExceptionFichier("Erreur lors de l'ouverture du fichier "+nomFichier+" !");
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
		for(int j=0; j+1<this->getVecteur(i).size();j++){
			Adjacence<TypeValeur> a(this->getElement(i,j),this->getElement(i,j+1));
			liste.push_back(a);
		}
	}
	return liste;
}

template<typename TypeValeur>
vector<Adjacence<TypeValeur> > Sequence<TypeValeur>::listeAdjacence(int i) const
{
	vector<Adjacence<TypeValeur> > liste;
	for(int j=0; j+1<this->getVecteur(i).size();j++){
			Adjacence<TypeValeur> a(this->getElement(i, j),this->getElement(i, j+1));
			liste.push_back(a);
	}
	return liste;
}

template<typename TypeValeur>
Alignement Sequence<TypeValeur>::calculAlignement(const std::vector<Marqueur<TypeValeur> >& s, int sub, int indel, int match) const
{
	int gauche; //valeur si on vient de la gauche
	int diag; //valeur si on vient de la diagonale
	int haut; //valeur si on vient du haut
	
	Alignement mat(this->getVecteur(0).size()+1,s.size()+1);

	mat.setElement(0,0,0);
	
	/*Initialisation ligne et colonne 0 :*/
	for(int i=1;i<this->getVecteur(0).size()+1;i++)
	{
		mat.setElement(i,0,0);
	}
	for(int j=1;j<s.size()+1;j++)
	{
		mat.setElement(0,j,0);
	}
	
	/*Calcul des valeurs de la matrice*/
	for(int i=1;i<this->getVecteur(0).size()+1;i++)
	{
		for(int j=1;j<s.size()+1;j++)
		{
			/*Calcul des 3 valeurs possibles pour mat[i][j]*/
			gauche=mat.getElement(i,j-1)+indel;
			haut=mat.getElement(i-1,j)+indel;
			
			if(this->getElement(0,i-1).getValeur()==s[j-1].getValeur()) //Modif pour pas prendre en compte orientation dans comparaison
			{
				diag=mat.getElement(i-1,j-1)+match;
			}
			else
			{
				diag=mat.getElement(i-1,j-1)+sub;
			}
			if(indel<0){
			/*Calcul de la valeur la plus grande pour mettre dans mat[i][j]*/
			if(gauche>haut)
			{
				if(gauche>diag)
				{
					mat.setElement(i,j,gauche);
				}
				else
				{
					mat.setElement(i,j,diag);
				}
			}
			else
			{
				if(haut>diag)
				{
					mat.setElement(i,j,haut);
				}
				else
				{
					mat.setElement(i,j,diag);
				}
			}
			}else
			{
				if(gauche<haut)
			{
				if(gauche<diag)
				{
					mat.setElement(i,j,gauche);
				}
				else
				{
					mat.setElement(i,j,diag);
				}
			}
			else
			{
				if(haut<diag)
				{
					mat.setElement(i,j,haut);
				}
				else
				{
					mat.setElement(i,j,diag);
				}
			}
			}
		}
	}
		
	return mat; //On retourne la dernière case de la matrice (le score)
}


template<typename TypeValeur>
void Sequence<TypeValeur>::alignementLocal(const Sequence<TypeValeur>& s, int sub, int indel, int match) const throw(ExceptionFichier)
{
	extern bool log,logDetaille;
	extern string nomFichier;
	ofstream fichier;
	
	if(log==true){
		fichier.open(nomFichier.c_str(),ios::out|ios::app); //On ouvre le fichiers et on place le curseur à la fin pour ne pas écrire par dessus d'autres données du fichier de sortie.
		if(!fichier){
			throw ExceptionFichier("Erreur lors de l'ouverture du fichier "+nomFichier+" !");
		}
			
		fichier<<"Algorithme : Alignement local";
		if(logDetaille){
			fichier<<endl<<"Sequence 1 : ";
			this->affichage(fichier);
			fichier<<endl<<"Sequence 2 : ";
			s.affichage(fichier);
			fichier<<endl;
		}
		fichier<<endl<<"Coût substitution : "<<sub<<endl;
		fichier<<"Coût insertion/deletion : "<<indel<<endl;
		fichier<<"Coût de correspondance : "<<match<<endl;
		fichier<<"========================================================================"<<endl;
	}
	
	// On applique l'algo d'alignement à chaque sous-séquence de s
	for (int i = 0; i < s.nbSousSeq(); i++)
	{
		Alignement matrice = this->calculAlignement(s.getVecteur(i), sub, indel, match);
		if(log){
			if(logDetaille){
				fichier<<"Sequence 2."<<i+1<<" : ";
				for(int j=0; j<s.getVecteur(i).size();j++){
				
					s.getElement(i,j).affiche(fichier);
					fichier<<" ";
				}
				fichier<<endl;
		
				matrice.affiche(fichier<<endl);
				fichier << endl;
			}
			if (indel < 0){
				fichier<< "\tScore alignement local : " << matrice.getResultat() << endl << endl;
			}
			else{ 
				fichier<< "\tDistance alignement local : " << matrice.getResultat() << endl << endl;
			}
		}
		
		if (indel < 0)
			cout << "Score alignement local : " << matrice.getResultat() << endl;
		else
			cout << "Distance alignement local : " << matrice.getResultat() << endl;
	}
	
	if(log==true)
		fichier.close();
}


template<typename TypeValeur>
int Sequence<TypeValeur>::adjacencesCommunes(const Sequence<TypeValeur>& s) const throw(ExceptionFichier){

	extern bool log,logDetaille;
	extern string nomFichier;
	ofstream fichier;
	
	if(log==true){
		fichier.open(nomFichier.c_str(),ios::out|ios::app); //On ouvre le fichiers et on place le curseur à la fin pour ne pas écrire par dessus d'autres données du fichier de sortie.
		if(!fichier){
			throw ExceptionFichier("Erreur lors de l'ouverture du fichier "+nomFichier+" !");
		}
		
		fichier<<"Algorithme : Breakpoint"<<endl;
		if(logDetaille){
			fichier<<"Sequence 1 : ";
			this->affichage(fichier);
			fichier<<endl<<"Sequence 2 : ";
			s.affichage(fichier );
			fichier<<endl;
		}
		fichier<<"========================================================================"<<endl;
		
		//affichage de l'intersection
		fichier << "adjacences communes aux 2 sequences : "<< endl ;
	}
	
	int nbAdjacencesCommunes = 0;
	vector<Adjacence<TypeValeur> > liste1 = this->listeAdjacence();
	
	for (int i = 0; i < s.nbSousSeq(); i++)
	{
		vector<Adjacence<TypeValeur> > liste2 = s.listeAdjacence(i);
	
		sort(liste1.begin(),liste1.begin()+liste1.size()); //Tri des adjacences de la liste de this par ordre de valeur croissante pour la fonction set_intersection
		sort(liste2.begin(),liste2.begin()+liste2.size()); //Tri des adjacences de la liste de s par ordre de valeur croissante pour la fonction set_intersection
	
		vector<Adjacence<TypeValeur> > inter(liste1.size()+liste2.size()); //Création du tableau des intersection entre liste1 et liste2. Sa taille est égale à celle de liste1 ajoutée à celle de liste 2
		typename vector<Adjacence<TypeValeur> >::iterator it; //Itérateur sur la dernière intersection retenue
	
		it = set_intersection(liste1.begin(), liste1.begin()+liste1.size(),liste2.begin(),liste2.begin()+liste2.size(),inter.begin()); //Execution de la intersection entre les deux listes, stockage des intersection dans inter et stockage du nombre d'adjacences intersection dans it
		inter.resize(it-inter.begin()); //Modification de la taille de inter pour que celle ci soit égale au nombre de intersection stockées
		nbAdjacencesCommunes += inter.size();
		
		if(log){
			if(logDetaille){
				fichier<<"\tSequence 2."<<i+1<<" : ";
			
				for(int j=0; j<s.getVecteur(i).size();j++){
				
					s.getElement(i,j).affiche(fichier);
					fichier<<" ";
				}
				fichier<<endl;
			}
			for(it= inter.begin(); it!=inter.end(); it++ )
			{
				fichier <<"\t\t";
				it->getMarqueur1().affiche(fichier);
				fichier << " ";
				it->getMarqueur2().affiche(fichier);
				fichier << endl;
			}
		
			int scoreAbsolu = inter.size();
			float scoreRelatif = (float)scoreAbsolu/(this->getVecteur(i).size()-1);
		
			fichier << endl <<"\tScore absolu : "<< scoreAbsolu << endl;
			fichier <<"\tScore relatif : " << scoreRelatif << endl << endl;
		}
	}
	
	if(log==true){
		fichier.close();
	}
	
	return nbAdjacencesCommunes; //Nombre d'intersection retourné
}

/*
template<typename TypeValeur>
void Sequence<TypeValeur>::preproscessing(vector<Marqueur<TypeValeur>*>& s1, Sequence& s2, 
		map<Marqueur<TypeValeur>,vector<int> >& pos, int num[][]) const
{

}*/

template<typename TypeValeur>
int Sequence<TypeValeur>::intervallesCommuns(const Sequence<TypeValeur>& s) const throw(ExceptionFichier)
{	
	extern bool log, logDetaille;
	extern string nomFichier;
	ofstream fichier;
	
	//Si log, ouverture du fichier dans lequel on mettra le resultat de la fonction :
	if(log==true){
		fichier.open(nomFichier.c_str(),ios::out|ios::app); //On ouvre le fichiers et on place le curseur à la fin pour ne pas écrire par dessus d'autres données du fichier de sortie.
		if(!fichier){
			throw ExceptionFichier("Erreur lors de l'ouverture du fichier "+nomFichier+" !");
		}
		
		fichier<<"Algorithme : Intervalles Communs"<<endl;
		if(logDetaille){
			fichier<<"Sequence 1 : ";
			this->affichage(fichier);
			fichier<<endl<<"Sequence 2 : ";
			s.affichage(fichier );
			fichier<<endl;
		}
		fichier<<"========================================================================"<<endl;
	}

	//Partie 1: Init
	
	// Création de nouvelles séquences ne prenant pas en compte les signes
	vector<Marqueur<TypeValeur> > s1;

	// Création d'un vecteur avec l'ensemble des marqueurs de la 1e sous-séquence de s1
	for(int j=0; j< this->getVecteur(0).size(); j++){
		Marqueur<TypeValeur> m = this->sequence[0][j];
		m.setOrientation('+');
		s1.push_back(m);
	}
	
	
	map<Marqueur<TypeValeur>,vector<int> > pos;			// Liste des positions de chaque Marqueur dans s1
	int **num=new int*[s1.size()];				// Nombre de marqueurs différents entre les pos i et j dans s1

	for(int i=0;i<s1.size();i++){
		num[i]=new int[s1.size()];
	}
	
	// Remplissage de pos : parcours de s1 et ajout des positions pour chaque marqueur
	for(int i=0; i< s1.size();i++){
		pos[s1[i]].push_back(i);
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
				for(int k = i; k<=j;k++){
					if(find(present.begin(), present.end(), s1[k]) == present.end()){		// Si le marqueur n'existe pas, on l'ajoute
						present.push_back(s1[k]);
					}
				}
				
				// On stocke le nombre de marqueurs différents trouvés
				num[i][j]= present.size();
			}
		}
	}
	
	// Partie 2: Algo
	
	/* Vecteur des résultats, chaque ligne comprend 4 valeurs : 
		début et fin de l'intervalle commun dans s1
		début et fin de l'intervalle commun dans s2
	*/
	vector<vector<int> > output;
	
	
	// Parcours S2

	for (int t = 0; t < s.nbSousSeq(); t++)
	{	
		int cpt=0;
		if(log==true){
			if(logDetaille){
				fichier<<"Sequence 2."<<t+1<<" : ";
			
				for(int i=0; i<s.getVecteur(t).size();i++){
				
					s.getElement(t,i).affiche(fichier);
					fichier<<" ";
				}
				fichier<<endl;
			}
		}
		vector<Marqueur<TypeValeur> > s2;
		
		// Création d'un vecteur avec l'ensemble des marqueurs de la sous-séquence de s2
		for(int j=0; j< s.getVecteur(t).size(); j++){
			Marqueur<TypeValeur> m = s.sequence[t][j];
			m.setOrientation('+');
			s2.push_back(m);
		}
		
		
		// Pointeur i représentant le début de l'intervalle courant sur s2
		int i = 0;
		
		// On déplace le ptr i
		while(i<s2.size())
		{
			// Pointeur j représentant la fin de l'intervalle courant sur s2
			int j = i;
			bool elementsVusS1[s1.size()];			// Chaque case du tableau est vrai si le marqueur est compris entre les pointeurs i et j
			for (int j = 0; j < s1.size(); j++)
			{
				elementsVusS1[j] = 0;
			}
		
			vector<Marqueur<TypeValeur> > elementsS2;		// Elements entre i et j

			// On déplace le ptr j
			while(j< s2.size() && !pos[s2[j]].empty())
			{
				// Si on a pas vu l'élément
				if(find(elementsS2.begin(), elementsS2.end(), s2[j]) == elementsS2.end() )
				{
					// on l'ajoute
					elementsS2.push_back(s2[j]);
					
					// On encadre dans s1 avec pos
					for(int k= 0 ; k<pos[s2[j]].size();k++ )
					{
						elementsVusS1[pos[s2[j]][k]]=1; // encadrement (marqué comme vu)
					}
				
					// on étend à droite
					while(j+1 < s2.size() && find(elementsS2.begin(), elementsS2.end(), s2[j+1]) != elementsS2.end() )
					{
						j++;
					}
				}
	
				
				// Si l'élément avant i se trouve aussi entre i et j, on a pas étendu à gauche
				// On affiche le résultat si i n'a pas de précédent ou si l'élément d'avant n'est pas entre i et j
				if(i == 0 || find(elementsS2.begin(), elementsS2.end(), s2[i-1]) == elementsS2.end() )
				{	
					//parcours du tableau de booléens
					int l = 0;
					while (l < s1.size())
					{
						int debut, fin;
				
						// Debut et fin représentent un encadrement continu
						if(elementsVusS1[l] == 1)
						{
							debut=l;
							fin=l;
							while(l+1 < s1.size() && elementsVusS1[l+1] == 1)
							{
								fin++;
								l++;
							}
						}
						else
						{
							debut = -1;
							fin = -1;
						}
				
						// Si on a un encadrement comportant le nombre d'éléments différents entre i et j, on affiche
						if (debut != -1 && fin != -1)
						{
							if(num[debut][fin] == elementsS2.size() )
							{
								//ajout ligne output
								output.push_back(vector< int >());
								output.back().push_back(debut);
								output.back().push_back(fin);
								output.back().push_back(i);
								output.back().push_back(j);
								cpt++;
								if(log==true){
									
									fichier <<"\t("<< debut+1 << " - " << fin+1 << ") - (" << i+1 << " - " << j+1 <<")"<< endl;
								}
								else{ //A ENLEVER PLUS TARD
									cout<< debut+1 << " - " << fin+1 << " - " << i+1 << " - " << j+1 << endl;
								}
							}
						}
						l++;
					}
				}			
				j++;
			}
		
			// on a étendu à gauche, on passe les mêmes élements
			Marqueur<TypeValeur> valprec(s2[i]);
	
			while(i<s2.size() && s2[i] == valprec)
			{
				i++;
			}
		}
		
		if(log==true){
			fichier<<"Nombre d'intervalles communs : "<<cpt<<endl<<endl;
		}
	}
	if(log==true){
		fichier<<"Nombre total d'intervalles communs : "<<output.size()<<endl;
		fichier<<endl << endl;
		fichier.close(); //fermeture du ficher car on a fini d'écrire dedans
	}

	
	//On libère la mémoire :
	for(int i =0; i<s1.size();i++){
		delete [] num[i];
	}
	delete [] num;
	
	
	return output.size();
}



