#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), grille(new Grid)
{
    setWindowTitle(tr("Tetris"));
    resize(854,480);

    layout = new QGridLayout;

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    levelLCD = new QLCDNumber(3);
    scoreLCD = new QLCDNumber(5);

    connect(startButton, &QPushButton::clicked, grille, &Grid::start);
    connect(grille, &Grid::levelChanged, levelLCD, qOverload<int>(&QLCDNumber::display));
    connect(grille, &Grid::scoreChanged, scoreLCD, qOverload<int>(&QLCDNumber::display));

    layout->addWidget(createLabel(tr("Level")), 0, 0);
    layout->addWidget(levelLCD, 1, 0);
    layout->addWidget(createLabel(tr("Score")), 2, 0);
    layout->addWidget(scoreLCD, 3, 0);
    layout->addWidget(grille, 0, 1, 6, 1);
    layout->addWidget(startButton, 5, 2);
    setLayout(layout);

}

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

MainWindow::~MainWindow()
{
    delete grille;
}

