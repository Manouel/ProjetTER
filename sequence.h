#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include "truc.h"


class Sequence{
	private:
		vector<vector<Truc>> sequence;
	public:
		
		Sequence();
		//Sequence(const Sequence& sequ);
		vector<vector<Truc>> getSequence() const;
		void ajoutElement(Truc& t);
		void supElement(Truc& t);
		bool rechercheElement(const Truc& t);
		
	
};


#endif
