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

    if (!fichier.isNull())
    {
        chemin.setText(fichier);
    }
}
