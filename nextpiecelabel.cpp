#include <iostream>
#include "nextpiecelabel.h"

nextPieceLabel::nextPieceLabel(QWidget *parent)
    : nextPiece(new Piece)
{

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::NoFocus);

}

nextPieceLabel::~nextPieceLabel()
{
    delete nextPiece;
}

void nextPieceLabel::paintEvent(QPaintEvent *event)
{
    QColor tableColor[8] = {0xffffff, 0x00ffff, 0xffff00, 0xaa00ff, 0xffa500, 0x0000ff, 0xff0000, 0x00ff00};

    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();

    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawRect(rect);

    Forme shape = nextPiece->getShape();

    std::cout << "PAINT EVENT, NEXTPIECE = " << nextPiece->getShape() << std::endl;

    if (shape != noShape){

        for (int i(0); i<4; i++){

            int xPiece=nextPiece->getPosX(i) + 2;
            int yPiece=nextPiece->getPosY(i) + 2;

            QRect square(rect.left()+xPiece*squareWidth(),rect.top()+yPiece*squareHeight(), squareWidth(), squareHeight());

            painter.drawRect(square);
            painter.fillRect(square, tableColor[shape]);
        }
    }
}

void nextPieceLabel::newNextPiece(Piece* newPiece)
{
    nextPiece = newPiece;

    update();
}
