#ifndef FENETRE_H
#define FENETRE_H

#include <QTabWidget>
#include <QTextEdit>
#include <QSpinBox>
#include <QGroupBox>
#include <QRadioButton>
#include "EntreeSequence.h"
#include "CheminFichier.h"

class Fenetre : public QWidget
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
