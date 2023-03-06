#include "piece.h"

Piece::Piece(Forme newShape) : shape(newShape)
{

// Initialize the array with the positions of each shape
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

// Set the position of the piece to the corresponding value in the array
for (int i(0); i<4; i++){
    for (int j(0); j<2; j++){
        pos[i][j] = initPos[newShape][i][j];
    }
}

}

// This function sets the x-coordinate of the piece at the given index.
void Piece::setX(int index, int x){

    pos[index][0]=x;

}

// This function sets the y-coordinate of the piece at the given index.
void Piece::setY(int index, int y){

    pos[index][1]=y;

}

// This function returns the shape of the piece.
Forme Piece::getShape(){
    return shape;
}

// This function rotates the piece to the right by changing the x and y coordinates of the piece.
Piece* Piece::rotateRight()
{
    Piece *fpiece(new Piece(shape));
    for (int i(0); i<4; i++){
        fpiece->setX(i,-pos[i][1]);
        fpiece->setY(i,pos[i][0]);
    }

    return fpiece;

}

// This function rotates the piece to the left by changing the x and y coordinates of the piece.
Piece* Piece::rotateLeft(){

    Piece *fpiece(new Piece(shape));
    for (int i(0); i<4; i++){
        fpiece->setX(i,pos[i][1]);
        fpiece->setY(i,-pos[i][0]);
    }

    return fpiece;

}

// This function returns the x-coordinate of a piece at the given index
int Piece::getPosX(int index) 
{
    return pos[index][0];
}

// This function returns the y-coordinate of a piece at the given index
int Piece::getPosY(int index) 
{
    return pos[index][1];
}

