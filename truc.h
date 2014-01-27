#ifndef truc_h
#define truc_h

class Truc
{
private:
	int valeur;
	char orientation;
public:
	Truc();
	Truc(int val);
	Truc(int val, char ori);
	
	int getValeur()const;
	char getOrientation()const;
	
	void setValeur(int val);
	void setOrientation(char ori);
};

#endif
