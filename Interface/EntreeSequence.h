/*========================================================================
Nom: EntreeSequence.cpp           auteur: Manuel Chataigner
Maj:  22/05/2014           Creation: 22/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient les éléments permettant l'envoi d'une séquence à comparer
en entrée, en ligne de commande ou bien dans un fichier.
=========================================================================*/

#ifndef ENTREESEQUENCE_H
#define ENTREESEQUENCE_H

#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include "CheminFichier.h"

class EntreeSequence : public QGroupBox
{
    private:
        QRadioButton boutonTexte;
        QRadioButton boutonFichier;

        QLineEdit entree;
        CheminFichier fichier;

    public:
        EntreeSequence(QString titreBox);
        ~EntreeSequence();

        bool sequenceTexte() const;
        QString getSequence() const;

};

#endif // ENTREESEQUENCE_H
