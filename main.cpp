#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    QPushButton bouton("Hello World !");
    bouton.show();
    */

    /*
    Grid grille;
    grille.show();
    */


    MainWindow w;
    w.show();


    return a.exec();
}
