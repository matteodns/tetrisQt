#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>

#include "grid.h"

// The class MainWindow is a subclass of the QWidget class. It contains the following members:
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //  A pointer to an instance of the Grid class.
    Grid *grille;

    // A pointer to an instance of the QGridLayout class.
    QGridLayout *layout;

    // A function that creates a label with the given text.
    QLabel *createLabel(const QString &text);

    //  A pointer to an instance of the QPushButton class.
    QPushButton *startButton;

    // A pointer to an instance of the QLCDNumber class.
    QLCDNumber *levelLCD;

    // A pointer to an instance of the QLCDNumber class.
    QLCDNumber *scoreLCD;
};
#endif // MAINWINDOW_H
