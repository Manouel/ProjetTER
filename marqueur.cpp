#include "marqueur.h"
using namespace std;

Marqueur::Marqueur(){}
Marqueur::Marqueur(int val){this.valeur= val;}
Marqueur::Marqueur(int val, char ori){this.valeur= val; this.orientation= ori;}

int Marqueur::getValeur()const
{return this.valeur;}

char Marqueur::getOrientation()const
{return this.orientation;}

void Marqueur::setValeur(int val)
{this.valeur= val;}

void Marqueur::setOrientation(char ori)
{this.orientation= ori;}
