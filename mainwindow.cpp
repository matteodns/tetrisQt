#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), grille(new Grid)
{
    setWindowTitle(tr("Tetris"));
    resize(854,480);

    // Create a new QGridLayout
    layout = new QGridLayout;
    
    // Create a new QPushButton with text "Start"
    startButton = new QPushButton(tr("&Start"));

    // Disable focus on this button
    startButton->setFocusPolicy(Qt::NoFocus);
    
    // Create two LCDNumber objects for level and score
    levelLCD = new QLCDNumber(3);
    scoreLCD = new QLCDNumber(5);
    
    // Connect startButton's clicked signal to Grid's start slot
    connect(startButton, &QPushButton::clicked, grille, &Grid::start);

    // Connect Grid's levelChanged signal to levelLCD's display slot
    connect(grille, &Grid::levelChanged, levelLCD, qOverload<int>(&QLCDNumber::display));

    // Connect Grid's scoreChanged signal to scoreLCD's display slot
    connect(grille, &Grid::scoreChanged, scoreLCD, qOverload<int>(&QLCDNumber::display));

    // Create label for "Level" and add it to the layout
    layout->addWidget(createLabel(tr("Level")), 0, 0);

    // Add levelLCD to the layout
    layout->addWidget(levelLCD, 1, 0);

    // Create label for "Score" and add it to the layout
    layout->addWidget(createLabel(tr("Score")), 2, 0);

    // Add scoreLCD to the layout
    layout->addWidget(scoreLCD, 3, 0);

    // Add grille to the layout
    layout->addWidget(grille, 0, 1, 6, 1);

    // Add startButton to the layout
    layout->addWidget(startButton, 5, 2);

    // Set the layout of the MainWindow
    setLayout(layout);

}

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

// Destructor for MainWindow
MainWindow::~MainWindow()
{   
    // Delete the grille object
    delete grille;
}

