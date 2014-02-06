#include "sequence.h"


Sequence::Sequence(){}

vector<vector<Truc>> Sequence::getSequence() const{
	return this->sequence;
}

void Sequence::ajoutElement(Marqueur& t){

}

void Sequence::supElement(Marqueur& t){

}

bool Sequence::rechercheElement(Marqueur& t){

}

int alignementGlobal(const vector<Marqueur>& sequBis, int sub, int indel, int match) const
{
	int gauche; //valeur si on vient de la gauche
	int diag; //valeur si on vient de la diagonale
	int haut; //valeur si on vient du haut
	
	int mat[this->sequence[0].size()+1][sequBis.size()+1];
	
	mat[0][0]=0;
	
	/*Initialisation ligne et colonne 0 :*/
	for(int i=1;i<this->sequence[0].size()+1;i++)
	{
		mat[i][0]=mat[i-1][0]+indel;
	}
	for(int j=1;j<sequBis.size()+1;j++)
	{
		mat[0][j]=mat[0][j-1]+indel;
	}
	
	/*Calcul des valeurs de la matrice*/
	for(int i=1;i<this->sequence[0].size()+1;i++)
	{
		for(int j=1;j<sequBis.size()+1;j++)
		{
			/*Calcul des 3 valeurs possibles pour mat[i][j]*/
			gauche=mat[i][j-1]+indel;
			haut=mat[i-1][j]+indel;
			if(this->sequence[0][i]==seq[j])
			{
				diag=mat[i-1][j-1]+match;
			}
			else
			{
				diag=mat[i-1][j-1]+sub;
			}
			
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
			
			
		}	
	}
		
	return mat[this->sequence[0].size()][sequBis.size()]; //On retourne la dernière case de la matrice (le score)
}
