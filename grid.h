#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include "piece.h"

class Grid : public QFrame
{
    Q_OBJECT

public:

    // Constructor for the Grid class
    Grid(QWidget *parent =nullptr);

    // Destructor for the Grid class
    ~Grid();

    //void cleanBoard();

    // Returns the width of a single square in the grid
    int squareWidth();

    // Returns the height of a single square in the grid
    int squareHeight();

    // Tries to create a new random piece in the grid
    bool tryNewRandPiece();

    // Tries to rotate the given piece
    bool tryRotate(Piece *newPiece);

    // Tries to move the piece to the given coordinates
    bool tryMove(int newX, int newY);

    // Tries to move the piece down one row
    bool tryMoveDown();

    // Removes any full lines from the grid
    void removeLines();

    // Overrides the paint event of the QFrame class
    void paintEvent(QPaintEvent *event) override;

    // Overrides the key press event of the QFrame class
    void keyPressEvent(QKeyEvent *event) override;

    // Draws a single square in the grid
    void drawSquare();


public slots:

    // Starts the game
    void start();

signals:

    // Emitted when the level changes
    void levelChanged(int level);

    // Emitted when the score changes
    void scoreChanged(int score);

private:

    // The width of the grid
    int gridWidth = 10;

    // The height of the grid
    int gridHeight = 22;

    // The current score
    int score;

    // The current level
    int level;

    // The number of pieces dropped
    int pieceDropped;

    // The number of lines removed
    int linesRemoved;

    // An array of Forme representing a Tetris grid
    Forme grille[22][10];

    // A pointer to the current piece
    Piece *curPiece;

    // An array containing the x and y coordinates of the current piece
    int posCurPiece[2];

    // A boolean indicating wether the game has finished or not 
    bool isFinished;

    // A timer object used to control the game speed
    QTimer timer;

};

#endif // GRID_H
