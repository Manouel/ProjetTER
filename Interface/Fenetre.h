/*========================================================================
Nom: Fenetre.cpp           auteur: Manuel Chataigner
Maj:  22/05/2014           Creation: 02/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient la classe représentant la fenêtre, avec l'ensemble des 
éléments qui la composent.
=========================================================================*/

#ifndef FENETRE_H
#define FENETRE_H

#include <QTabWidget>
#include <QTextEdit>
#include <QSpinBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include "EntreeSequence.h"
#include "CheminFichier.h"

class Fenetre : public QScrollArea
{
    Q_OBJECT

    private:
        QTabWidget onglets;

        QSpinBox coutIndel;
        QSpinBox coutSubstitution;
        QSpinBox coutMatch;

        EntreeSequence seq1;
        EntreeSequence seq2;
        QLineEdit separateur;

        QGroupBox boxLogs;
        QRadioButton logSimplifie;
        QRadioButton logDetaille;
        CheminFichier fichierLogs;
        QTextEdit affichageLogs;

    public:
        Fenetre();
        ~Fenetre();

    public slots:
        void executeAlgo();

};

#endif // FENETRE_H
