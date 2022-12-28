#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), grille(new Grid)
{
    setWindowTitle(tr("Tetris"));
    resize(300,660);

    layout = new QGridLayout;

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, grille, &Grid::start);

    layout->addWidget(startButton, 4, 0);

    layout->addWidget(grille, 0, 0);
    setLayout(layout);

}

MainWindow::~MainWindow()
{
    delete grille;
}

