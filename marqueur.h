<<<<<<< HEAD:marqueur.h
#ifndef Marqueur_h
#define Marqueur_h
=======
#ifndef TRUC_H
#define TRUC_H
>>>>>>> DepotManu/master:truc.h

class Marqueur
{
private:
	int valeur;
	char orientation;
public:
<<<<<<< HEAD:marqueur.h
	Marqueur();
	Marqueur(int val);
	Marqueur(int val, char ori);
=======
	Truc();
	Truc(int val);
	Truc(int val, char ori);
	Truc(const Truc& nvT); //Constructeur par recopie
>>>>>>> DepotManu/master:truc.h
	
	int getValeur()const;
	char getOrientation()const;
	
	void setValeur(int val);
	void setOrientation(char ori);
};

#endif
