#ifndef ADJACENCE_H
#define ADJACENCE_H
#include "marqueur.h"


class Adjacence{

private:
	Marqueur marqueur1;
	Marqueur marqueur2;

public:
	Adjacence(Marqueur m1, Marqueur m2);
	Marqueur getMarqueur1() const;
	Marqueur getMarqueur2() const;
	
};

bool operator== (const Adjacence& a1, const Adjacence& a2);


#endif
