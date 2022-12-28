#include "grid.h"

#include <iostream>
using namespace std;


Grid::Grid(QWidget *parent)
    : QFrame(parent), isFinished(false), curPiece(new Piece)
{

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);

    for (int i(0); i<22; i++) {
        for (int j(0); j<10; j++ ){
            grille[i][j] = noShape;
        }
    }

    connect(&timer,&QTimer::timeout,this,&Grid::tryMoveDown);

}

Grid::~Grid()
{
    delete curPiece;
}

int Grid::squareWidth()
{
    return contentsRect().width()/gridWidth;
}

int Grid::squareHeight()
{
    return contentsRect().height()/gridHeight;
}

bool Grid::tryNewRandPiece()
{

    Forme newShape(Forme(rand()%7+1));
    Piece *newPiece = new Piece(newShape);

    posCurPiece[0] = gridWidth/2-1;
    posCurPiece[1] = 0;  //à modifier si nouvelles piece (avec un ymin != 0)

    for (int i(0); i<4; i++){

        int yPiece(newPiece->getPosY(i));
        int xPiece(newPiece->getPosX(i));

        yPiece+=posCurPiece[1];
        xPiece+=posCurPiece[0];

        if (grille[yPiece][xPiece] != noShape){

            delete newPiece;

            isFinished = true;

            timer.stop();

            update(); //fin de la partie !!!

            return false;

        }

    }

    curPiece=newPiece;

    update();

    return true;

}

bool Grid::tryRotate(Piece *newPiece)
{
    for (int i(0); i<4; i++){

        int yPiece(newPiece->getPosY(i));
        int xPiece(newPiece->getPosX(i));

        yPiece += posCurPiece[1];
        xPiece += posCurPiece[0];

        if (yPiece<0 || yPiece>=gridHeight || xPiece<0 || xPiece>=gridWidth || grille[yPiece][xPiece] != noShape){

            delete newPiece;

            return false;
        }

    }

    curPiece=newPiece;

    update();

    return true;

}

bool Grid::tryMove(int newX, int newY)
{
    for (int i(0); i<4; i++){
        int yPiece(curPiece->getPosY(i));
        int xPiece(curPiece->getPosX(i));

        yPiece += newY;
        xPiece += newX;

        Forme nvPos = grille[yPiece][xPiece];

        if (yPiece<0 || yPiece>=gridHeight || xPiece<0 || xPiece>=gridWidth || nvPos != noShape){

            return false;
        }

    }

    posCurPiece[0]=newX;
    posCurPiece[1]=newY;     //check si il arrive en bas ?
                                //separer trymove et trymovedown

    update();

    return true;

}

bool Grid::tryMoveDown()
{
    if(!tryMove(posCurPiece[0],posCurPiece[1]+1))
    {
        //changer score

        for (int i(0); i<4; i++){
            grille[curPiece->getPosY(i)+posCurPiece[1]][curPiece->getPosX(i)+posCurPiece[0]] = curPiece->getShape();
        }

        removeLines();
        tryNewRandPiece();

        return false;
    }

    return true;
}

void Grid::start()
{   cout << "start" << endl;
    timer.start(1000);
    tryNewRandPiece();
}

/* void Grid::cleanBoard()
{



} */

void Grid::paintEvent(QPaintEvent *event)
{
    QColor tableColor[8] = {0xffffff, 0x00ffff, 0xffff00, 0xaa00ff, 0xffa500, 0x0000ff, 0xff0000, 0x00ff00};

    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();

    if(isFinished){
        QMessageBox::information(this,"Fin de la partie", "Partie Finie");
        return;
    }

    painter.drawRect(rect);

    for (int i(0); i<gridHeight; i++){
        for (int j(0); j<gridWidth; j++){

            Forme shape = grille[i][j];

            if (shape != noShape){

                QRect square(rect.left()+j*squareWidth(), rect.top()+i*squareHeight(), squareWidth(), squareHeight());

                painter.drawRect(square);
                painter.fillRect(square, tableColor[shape]);
            }

        }
    }

    Forme curShape=curPiece->getShape();
    for (int i(0); i<4; i++)
    {
        int xPiece=curPiece->getPosX(i) + posCurPiece[0];
        int yPiece=curPiece->getPosY(i) + posCurPiece[1];

        QRect curSquare(rect.left()+xPiece*squareWidth(), rect.top()+yPiece*squareHeight(), squareWidth(), squareHeight());

        painter.drawRect(curSquare);
        painter.fillRect(curSquare, tableColor[curShape]);
    }

}

void Grid::keyPressEvent(QKeyEvent *event)
{
    if (isFinished){
        QWidget::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(posCurPiece[0]-1, posCurPiece[1]);
        break;
    case Qt::Key_Right:
        tryMove(posCurPiece[0]+1, posCurPiece[1]);
        break;
    case Qt::Key_Up:
        tryRotate(curPiece->rotateLeft());
        break;
    case Qt::Key_Down:
        tryRotate(curPiece->rotateRight());
        break;
    case Qt::Key_Space:
        tryMoveDown();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Grid::removeLines()
{   cout << "removeLines" << endl;
    for (int i(gridHeight-1); i>=0; i--){
        bool lineFull(true);
        for (int j(0); j<gridWidth; j++)
        {
            cout << i << ";" << j << ";" << grille[i][j] << endl;
            if (grille[i][j]==0){
                lineFull=false;
                break;
            }
        }

        if (lineFull)
        {   cout << "line full" << endl;

            for (int k(i);k>0; k--){
                for (int j(0); j<gridWidth; j++){
                    grille[k][j] = grille[k-1][j];
                }
            }
        }
    }

    update();
}

























