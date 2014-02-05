#ifndef MARQUEUR_H
#define MARQUEUR_H

class Marqueur
{
  private:
	  int valeur;
	  char orientation;
	  
  public:
	  Marqueur();
	  Marqueur(int val);
	  Marqueur(int val, char ori);
	  Marqueur(const Marqueur& nvT); //Constructeur par recopie
	
	  int getValeur()const;
	  char getOrientation()const;
	
	  void setValeur(int val);
	  void setOrientation(char ori);
};

#endif
