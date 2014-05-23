/*========================================================================
Nom: CheminFichier.cpp           auteur: Manuel Chataigner
Maj:  22/05/2014           Creation: 22/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient l'implémentation des fonctions de la classe CheminFichier.
=========================================================================*/

#include "CheminFichier.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>

CheminFichier::CheminFichier(QString placeholderText) : QWidget()
{
    chemin.setReadOnly(true);
    chemin.setPlaceholderText(placeholderText);

    QPushButton *rechercheFichier = new QPushButton("Parcourir");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(&chemin);
    layout->addWidget(rechercheFichier);

    setLayout(layout);

    connect(rechercheFichier, SIGNAL(clicked()), this, SLOT(chargementFichier()));
}

CheminFichier::~CheminFichier()
{

}

QString CheminFichier::getChemin() const
{
    return chemin.text();
}

void CheminFichier::chargementFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "");

    if(!fichier.isNull())
    {
        chemin.setText(fichier);
    }
}
