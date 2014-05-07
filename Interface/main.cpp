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
