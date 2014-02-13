#include "adjacence.h"

using namespace std;


Adjacence::Adjacence(Marqueur m1, Marqueur m2){
	this->marqueur1=m1;
	this->marqueur2=m2;
}

Marqueur Adjacence::getMarqueur1() const{
	return this->marqueur1;
}

Marqueur Adjacence::getMarqueur2() const{
	return this->marqueur2;	
}

bool operator== (const Adjacence& a1, const Adjacence& a2){
	
	if(a1.getMarqueur1()==a2.getMarqueur1())
	{
		if(a1.getMarqueur2()==a2.getMarqueur2())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(a1.getMarqueur1().getValeur()==a2.getMarqueur2().getValeur())
		{
			if(a1.getMarqueur2().getValeur()==a2.getMarqueur1().getValeur())
			{
				return true;
			}
		}
	
	}
	return false;
}
