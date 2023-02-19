#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>

#include "grid.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Grid *grille;
    QGridLayout *layout;

    QLabel *createLabel(const QString &text);

    QPushButton *startButton;
    QLCDNumber *levelLCD;
    QLCDNumber *scoreLCD;
};
#endif // MAINWINDOW_H
