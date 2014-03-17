#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H

class Alignement{
	private:
		int** mat;
		int lignes;
		int colonnes;
	
	public:
		Alignement(int lignes, int colonnes);
		~Alignement();
		
		int getElement(int i,int j) const;
		int getResultat() const;
		void setElement(int i, int j, int val);
};



#endif
