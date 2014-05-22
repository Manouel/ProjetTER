/*========================================================================
Nom: exceptionFichier.h           auteur: Jonathan Dufetel
Maj:  22/05/2014           Creation: 14/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe ExceptionFichier permettant de lever
une exception lors de l'ouverture d'un fichier. 
=========================================================================*/

#ifndef EXCEPTIONFICHIER_H
#define EXCEPTIONFICHIER_H

#include <string>
#include <exception>

class ExceptionFichier : public virtual std::exception
{
	private:
		std::string contexteException;
		
	public:
		ExceptionFichier();
		ExceptionFichier(std::string contexte);
		virtual ~ExceptionFichier() throw();
		virtual std::string verdict() const throw();
};

#endif
