/*========================================================================
Nom: marqueurType.cpp           auteur: Manuel Chataigner
Maj:  14/03/2014           Creation: 14/03/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la liste des directives d'instanciation explicites.
=========================================================================*/

#include <string>
#include "marqueur.cpp"
#include "sequence.cpp"
#include "adjacence.cpp"


template class Marqueur<int>;
template class Marqueur<char>;
template class Marqueur<std::string>;

template class Sequence<int>;
template class Sequence<char>;
template class Sequence<std::string>;

template class Adjacence<int>;
template class Adjacence<char>;
template class Adjacence<std::string>;

