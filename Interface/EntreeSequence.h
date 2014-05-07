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
