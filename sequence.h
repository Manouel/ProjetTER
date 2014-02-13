#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <string>
#include "marqueur.h"
using namespace std;


class Sequence{
	private:
		vector<vector<Marqueur> > sequence;
	public:
		
		Sequence();
		Sequence(const string& nomFichier);
		//Sequence(const Sequence& sequ);
		
		vector<vector<Marqueur> > getSequence() const;
		Marqueur getElement(int i, int j) const;
		vector<Marqueur> getVecteur(int i) const;
		
		int nbSousSeq() const;
		
		void ajoutElement(Marqueur& t);
		void ajoutSousSeq();
		void supElement(Marqueur& t);
		bool rechercheElement(const Marqueur& t);
		
		void load(const string& nomFichier);
		void save(const string& nomFichier);
		
		void affichage() const;
		
		
		/* Algo alignement global */
		
		/**
		 @param sequBis sequence à comparer avec this
		 @param sub, inser, delet, match valeur des couts des opérations
		 @return score
		*/
		int alignementGlobal(const vector<Marqueur>& sequBis, int sub, int indel, int match) const;
};


#endif
