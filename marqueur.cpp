#include "marqueur.h"

using namespace std;

Marqueur::Marqueur(){}
Marqueur::Marqueur(int val){this->valeur= val;}
Marqueur::Marqueur(int val, char ori){this->valeur= val; this->orientation= ori;}
Marqueur::Marqueur(const Marqueur& nvT){this->valeur=nvT.valeur; this->orientation=nvT.orientation;}

int Marqueur::getValeur() const
{return this->valeur;}

char Marqueur::getOrientation() const
{return this->orientation;}

void Marqueur::setValeur(int val)
{this->valeur= val;}

void Marqueur::setOrientation(char ori)
{this->orientation= ori;}

bool operator== (const Marqueur& m1, const Marqueur& m2){
	return m1.getValeur() == m2.getValeur();
}
