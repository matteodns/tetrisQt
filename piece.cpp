#include "piece.h"

Piece::Piece(Forme newShape) : shape(newShape)
{

    int initPos[8][4][2] = {
        {{0,0},{0,0},{0,0},{0,0}},
        {{-1,0},{0,0},{1,0},{2,0}},
        {{0,0},{1,0},{0,1},{1,1}},
        {{-1,0},{0,0},{1,0},{0,1}},
        {{-1,0},{0,0},{1,0},{-1,1}},
        {{-1,0},{0,0},{1,0},{1,1}},
        {{-1,0},{0,0},{0,1},{1,1}},
        {{-1,1},{0,1},{0,0},{1,0}},
    };

    for (int i(0); i<4; i++){
        for (int j(0); j<2; j++){
            pos[i][j] = initPos[newShape][i][j];
        }
    }

}


void Piece::setX(int index, int x){

    pos[index][0]=x;

}


void Piece::setY(int index, int y){

    pos[index][1]=y;

}

Forme Piece::getShape(){
    return shape;
}


Piece* Piece::rotateRight()
{
    Piece *fpiece(new Piece(shape));
    for (int i(0); i<4; i++){
        fpiece->setX(i,-pos[i][1]);
        fpiece->setY(i,pos[i][0]);
    }

    return fpiece;

}

Piece* Piece::rotateLeft(){

    Piece *fpiece(new Piece(shape));
    for (int i(0); i<4; i++){
        fpiece->setX(i,pos[i][1]);
        fpiece->setY(i,-pos[i][0]);
    }

    return fpiece;

}

int Piece::getPosX(int index)
{
    return pos[index][0];
}

int Piece::getPosY(int index)
{
    return pos[index][1];
}
