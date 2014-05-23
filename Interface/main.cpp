/*========================================================================
Nom: main.cpp           auteur: Manuel Chataigner
Maj:  22/05/2014           Creation: 02/04/2014
Projet: Comparaison de séquences de gènes
--------------------------------------------------------------------------
Specification:
Ce fichier contient le main de l'interface graphique et la création de
l'objet Fenetre.
=========================================================================*/

#include <QApplication>
#include <QTextCodec>
#include "Fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    Fenetre fenetre;
    fenetre.show();

    return app.exec();
}
