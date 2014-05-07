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
