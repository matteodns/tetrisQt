#ifndef NEXTPIECELABEL_H
#define NEXTPIECELABEL_H

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include "piece.h"

class nextPieceLabel : public QFrame
{
    Q_OBJECT

public:

    nextPieceLabel(QWidget *parent =nullptr);

    ~nextPieceLabel();

    int squareWidth(){return contentsRect().width()/5;};

    int squareHeight(){return contentsRect().height()/5;};

    void paintEvent(QPaintEvent *event) override;

public slots:

    void newNextPiece(Piece* newPiece);

private:

    Piece* nextPiece;



};

#endif // NEXTPIECELABEL_H
