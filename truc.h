#ifndef TRUC_H
#define TRUC_H

class Truc
{
private:
	int valeur;
	char orientation;
public:
	Truc();
	Truc(int val);
	Truc(int val, char ori);
	Truc(const Truc& nvT); //Constructeur par recopie
	
	int getValeur()const;
	char getOrientation()const;
	
	void setValeur(int val);
	void setOrientation(char ori);
};

#endif
