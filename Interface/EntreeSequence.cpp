#include "EntreeSequence.h"
#include <QVBoxLayout>

EntreeSequence::EntreeSequence(QString titreBox) : QGroupBox(titreBox), fichier("Fichier contenant la séquence")
{
    QVBoxLayout *layout = new QVBoxLayout();

    boutonTexte.setText("Ligne de commande");
    boutonFichier.setText("Fichier");
    entree.setPlaceholderText("Séquence à entrer");

    layout->addWidget(&boutonTexte);
    layout->addWidget(&entree);
    layout->addWidget(&boutonFichier);
    layout->addWidget(&fichier);

    setLayout(layout);

    connect(&boutonTexte, SIGNAL(toggled(bool)), &entree, SLOT(setEnabled(bool)));
    connect(&boutonTexte, SIGNAL(toggled(bool)), &fichier, SLOT(setDisabled(bool)));

    connect(&boutonFichier, SIGNAL(toggled(bool)), &entree, SLOT(setDisabled(bool)));
    connect(&boutonFichier, SIGNAL(toggled(bool)), &fichier, SLOT(setEnabled(bool)));

    boutonTexte.setChecked(true);
}

EntreeSequence::~EntreeSequence()
{

}

bool EntreeSequence::sequenceTexte() const
{
    return boutonTexte.isChecked();
}

QString EntreeSequence::getSequence() const
{
    if (boutonTexte.isChecked())
    {
        return entree.text();
    }
    else
    {
        return fichier.getChemin();
    }
}
