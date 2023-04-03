#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), grille(new Grid)
{
    setWindowTitle(tr("Tetris"));
    resize(854,465);

    // Create a new QGridLayout
    layout = new QGridLayout;
    
    // Create a new QPushButton with text "Start"
    startButton = new QPushButton(tr("&Start"));

    // Disable focus on this button
    startButton->setFocusPolicy(Qt::NoFocus);

    // Create a new QPushButton with text "Quit"
    quitButton = new QPushButton(tr("&Quit"));

    // Disable focus on this button
    quitButton->setFocusPolicy(Qt::NoFocus);
    
    // Create two LCDNumber objects for level and score
    levelLCD = new QLCDNumber(3);
    scoreLCD = new QLCDNumber(5);

    nextPiece = new nextPieceLabel(this);
    
    // Connect startButton's clicked signal to Grid's start slot
    connect(startButton, &QPushButton::clicked, grille, &Grid::start);

    // Connect quitButton's clicked signal to MainWindow's quit function
    connect(quitButton, &QPushButton::clicked, this, &exit);

    // Connect Grid's levelChanged signal to levelLCD's display slot
    connect(grille, &Grid::levelChanged, levelLCD, qOverload<int>(&QLCDNumber::display));

    // Connect Grid's scoreChanged signal to scoreLCD's display slot
    connect(grille, &Grid::scoreChanged, scoreLCD, qOverload<int>(&QLCDNumber::display));


    connect(grille, &Grid::nextPieceChanged, nextPiece,&nextPieceLabel::newNextPiece);

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

    // Add quitButton to the layout
    layout->addWidget(quitButton, 4, 2);

    // Create label for "Next" and add it to the layout
    layout->addWidget(createLabel(tr("Next")), 0, 2);

    // Add nextPieceFrame to the layout
    layout->addWidget(nextPiece, 1, 2, 2, 1);

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

