/*========================================================================
Nom: CheminFichier.cpp           auteur: Manuel Chataigner
Maj:  22/05/2014           Creation: 22/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient les éléments permettant la sélection d'un fichier
dans l'arborescence du système.
=========================================================================*/

#ifndef CHEMINFICHIER_H
#define CHEMINFICHIER_H

#include <QLineEdit>

class CheminFichier : public QWidget
{
    Q_OBJECT

    private:
        QLineEdit chemin;

    public:
        CheminFichier(QString placeholderText = "");
        ~CheminFichier();

        QString getChemin() const;

    public slots:
        void chargementFichier();
};

#endif // CHEMINFICHIER_H
