#include "Fenetre.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>

#include <sequence.h>
#include <exceptionFichier.h>
#include <logFichier.h>

using namespace std;

Fenetre::Fenetre() : QWidget(), seq1("Séquence 1"), seq2("Séquence 2"), fichierLogs("Résultats")
{
    setWindowTitle(tr("Comparaison d'ordre de gènes"));
    resize(810,300);


    QVBoxLayout *layoutPrincipal = new QVBoxLayout();

    QHBoxLayout *layout = new QHBoxLayout();

    QWidget *pageAlignement = new QWidget();
    QWidget *pageBreakpoints = new QWidget();
    QWidget *pageIntervalles = new QWidget();

    onglets.setUsesScrollButtons(false);
    onglets.addTab(pageAlignement, "Alignement local");
    onglets.addTab(pageBreakpoints, "Adjacences communes");
    onglets.addTab(pageIntervalles, "Intervalles communs");


    /* Alignement local */
    QFormLayout *layoutAlignement = new QFormLayout();

    coutIndel.setRange(-100, 100);
    coutMatch.setRange(-100, 100);
    coutSubstitution.setRange(-100, 100);

    layoutAlignement->addRow("Coût indel", &coutIndel);
    layoutAlignement->addRow("Coût match", &coutMatch);
    layoutAlignement->addRow("Coût substitution", &coutSubstitution);
    pageAlignement->setLayout(layoutAlignement);

    /* Breakpoints */


    /* Intervalles communs */


    QVBoxLayout *layoutFichiers = new QVBoxLayout();

    /* Entrées séquences */
    QGroupBox *boxSequences = new QGroupBox("Séquences");
    boxSequences->setObjectName("paramBox");
    boxSequences->setStyleSheet("QGroupBox#paramBox { font-weight:bold }");

    QVBoxLayout *layoutSequences = new QVBoxLayout();
    QLabel *texteSequences = new QLabel("Chargement des séquences à comparer : ");

    QFormLayout *layoutSeparateur = new QFormLayout();
    separateur.setPlaceholderText("Caractère séparateur des sous-séquences");
    layoutSeparateur->addRow("Séparateur", &separateur);

    layoutSequences->setSpacing(10);
    layoutSequences->setAlignment(Qt::AlignCenter);
    layoutSequences->addWidget(texteSequences);
    layoutSequences->addWidget(&seq1);
    layoutSequences->addWidget(&seq2);
    layoutSequences->addLayout(layoutSeparateur);
    boxSequences->setLayout(layoutSequences);

    /* ***************** */

    /* Logs */
    boxLogs.setTitle("Logs");
    boxLogs.setObjectName("paramBox");
    boxLogs.setStyleSheet("QGroupBox#paramBox { font-weight:bold }");
    boxLogs.setCheckable(true);
    boxLogs.setChecked(false);

    QVBoxLayout *layoutLogs = new QVBoxLayout();

    QLabel *texteLogs = new QLabel("Fichiers contenant les résultats de sortie : ");
    affichageLogs.setReadOnly(true);

    logSimplifie.setText("Logs Simplifiés");
    logDetaille.setText("Logs Détaillés");
    logSimplifie.setChecked(true);

    layoutLogs->setSpacing(10);
    layoutLogs->setAlignment(Qt::AlignCenter);
    layoutLogs->addWidget(&logSimplifie);
    layoutLogs->addWidget(&logDetaille);
    layoutLogs->addWidget(texteLogs);
    layoutLogs->addWidget(&fichierLogs);
    layoutLogs->addWidget(&affichageLogs);
    boxLogs.setLayout(layoutLogs);

    /* ***************** */

    layoutFichiers->addWidget(boxSequences);
    layoutFichiers->addWidget(&boxLogs);

    layout->addWidget(&onglets);
    layout->addLayout(layoutFichiers);


    QPushButton *run = new QPushButton(QIcon("run.png"), "Calculer !");
    QVBoxLayout *runLayout = new QVBoxLayout();
    runLayout->setAlignment(Qt::AlignCenter);
    runLayout->addWidget(run);

    layoutPrincipal->addLayout(layout);
    layoutPrincipal->addLayout(runLayout);

    setLayout(layoutPrincipal);

    connect(run, SIGNAL(clicked()), this, SLOT(executeAlgo()));
}

Fenetre::~Fenetre()
{

}

void Fenetre::executeAlgo()
{
    if (seq1.getSequence().isEmpty() || seq2.getSequence().isEmpty())
    {
        QMessageBox::critical(this, "Erreur fichiers séquences", "Les fichiers de séquences à comparer n'ont pas été correctement renseignés !");
        return;
    }

    if (separateur.text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur séparateur", "Le caractère séparateur de sous-séquences n'a pas été renseigné !");
        return;
    }

    Sequence<std::string> s1;
    Sequence<std::string> s2;

    char sep = separateur.text().at(0).toAscii();

    if (seq1.sequenceTexte()) {
        s1.remplirSequence(seq1.getSequence().toStdString(), sep);
    }
    else {
        try{
            s1.load(seq1.getSequence().toStdString(), sep);
        }
        catch(ExceptionFichier e){
            QMessageBox::critical(this, "Erreur fichiers séquences", "Erreur avec le fichier séquence 1 : " + QString::fromStdString(e.verdict()));
            return;
        }
    }

    if (seq2.sequenceTexte()) {
        s2.remplirSequence(seq2.getSequence().toStdString(), sep);
    }
    else {
        try{
            s2.load(seq2.getSequence().toStdString(), sep);
        }
        catch(ExceptionFichier e){
            QMessageBox::critical(this, "Erreur fichiers séquences", "Erreur avec le fichier séquence 2 : " + QString::fromStdString(e.verdict()));
            return;
        }
    }

    QString algo = onglets.tabText(onglets.currentIndex());

    /* Logs activés */
    if (boxLogs.isChecked())
    {
        LogFichier::log = true;

        if (!fichierLogs.getChemin().isEmpty())
        {
            LogFichier::nomFichier = fichierLogs.getChemin().toStdString();
        }

        if (logDetaille.isChecked())
        {
            LogFichier::logDetaille = true;
        }

        LogFichier l;
        std::string typeEntree1 = (seq1.sequenceTexte() ? "s" : "f");
        std::string typeEntree2 = (seq2.sequenceTexte() ? "s" : "f");
        std::string nomAlgo = "";
        if (algo == "Alignement local")
            nomAlgo = "AL";
        else if (algo == "Adjacences communes")
            nomAlgo = "AC";
        else if (algo == "Intervalles communs")
            nomAlgo = "IC";

        l.ecrireEnTete(typeEntree1, seq1.getSequence().toStdString(), typeEntree2, seq2.getSequence().toStdString(),
                       nomAlgo, s1.toString(), s2.toString());
    }

    if (algo == "Alignement local")
    {
        int sub = coutSubstitution.value(), indel = coutIndel.value(), match = coutMatch.value();
        s1.alignementLocal(s2, sub, indel, match);
    }
    else if (algo == "Adjacences communes")
    {
        try{
            int nbAdjacencesCommunes = s1.adjacencesCommunes(s2);
             affichageLogs.setText("Nombre d'adjacences communes : " + QString::number(nbAdjacencesCommunes));
        }
        catch(ExceptionFichier e){
            QMessageBox::critical(this, "Erreur", "ERREUR Fichier log Adjacences communes : "+QString::fromStdString(e.verdict()));
            return;
        }
    }
    else if (algo == "Intervalles communs")
    {
        try{
            affichageLogs.setText("Nombre d'intervalles communs : " + QString::number(s1.intervallesCommuns(s2)));
        }
        catch(ExceptionFichier e){
            QMessageBox::critical(this, "Erreur", "ERREUR Fichier log Intervalles Communs : " + QString::fromStdString(e.verdict()));
            return;
        }
    }

    QMessageBox::information(this, "Déroulement de l'algorithme", "Calculs de l'algorithme " + algo + " terminés avec succès !");
}
