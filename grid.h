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

    Grid(QWidget *parent =nullptr);
    ~Grid();

    //void cleanBoard();

    int squareWidth();
    int squareHeight();

    bool tryNewRandPiece();
    bool tryRotate(Piece *newPiece);
    bool tryMove(int newX, int newY);
    bool tryMoveDown();

    void removeLines();

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void drawSquare();


public slots:

    void start();

signals:

    void levelChanged(int level);
    void scoreChanged(int score);

private:

    int gridWidth = 10;
    int gridHeight = 22;

    int score;
    int level;
    int pieceDropped;
    int linesRemoved;

    Forme grille[22][10];
    Piece *curPiece;
    int posCurPiece[2];

    bool isFinished;

    QTimer timer;

};

#endif // GRID_H
