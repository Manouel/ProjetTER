#include <iostream>
#include "marqueur.h"
#include "sequence.h"

using namespace std;


int main()
{

/*
	Marqueur m1(3);
	Marqueur m2(3);
	cout<<"m1 :"<<m1.getValeur()<<endl;
	m1.setValeur(10);
	cout<<"m1 :"<<m1.getValeur()<<endl;
	
	Sequence seq1;
	seq1.ajoutElement(m1);
	seq1.ajoutElement(m2);
	
	seq1.affichage();
	
	seq1.ajoutSousSeq();
	Marqueur m3(7);
	seq1.ajoutElement(m3);
	
	seq1.affichage();
	*/
	
	/*
	Marqueur B(1);
	Marqueur A(2);
	Marqueur N(3);
	Marqueur E(4);
	Marqueur S(5);
	
	Sequence BANANE;
	Sequence ANANAS;
	
	BANANE.ajoutElement(B);
	BANANE.ajoutElement(A);
	BANANE.ajoutElement(N);
	BANANE.ajoutElement(A);
	BANANE.ajoutElement(N);
	BANANE.ajoutElement(E);
	
	ANANAS.ajoutElement(A);
	ANANAS.ajoutElement(N);
	ANANAS.ajoutElement(A);
	ANANAS.ajoutElement(N);
	ANANAS.ajoutElement(A);
	ANANAS.ajoutElement(S);
	
	BANANE.affichage();
	ANANAS.affichage();
	cout << endl;
	
	// this = ANANAS ; sequBis = BANANE
	cout<< "Score : " << ANANAS.alignementGlobal(BANANE.getVecteur(0),-1,-1,0)<<endl;	
	*/
	Sequence GGCTGAC;
	Sequence GATC("sequences.txt",'&');
	
	GATC.affichage();
	
	/**Marqueur G(1);
	Marqueur C(2);
	Marqueur T(3);
	Marqueur A(4);
	
	GGCTGAC.ajoutElement(G);
	GGCTGAC.ajoutElement(G);
	GGCTGAC.ajoutElement(C);
	GGCTGAC.ajoutElement(T);
	GGCTGAC.ajoutElement(G);
	GGCTGAC.ajoutElement(A);
	GGCTGAC.ajoutElement(C);
	
	GGCTGAC.save("test.txt",'&');
	
	/*GATC.ajoutElement(G);
	GATC.ajoutElement(A);
	GATC.ajoutElement(T);
	GATC.ajoutElement(C);
	
	cout<< "Dist : " << GATC.alignementGlobal(GGCTGAC.getVecteur(0),3,3,0)<<endl;
	*/
	return 0;
}
