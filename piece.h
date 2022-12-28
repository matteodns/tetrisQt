#ifndef PIECE_H
#define PIECE_H

enum Forme{noShape, iShape, oShape, tShape, lShape, jShape, zShape, sShape};

class Piece
{
public:

    Piece(Forme newShape = noShape);

    Piece* rotateRight();
    Piece* rotateLeft();

    int getPosX(int index);
    int getPosY(int index);
    Forme getShape();

private:

    void setX(int index, int x);
    void setY(int index, int y);

    int pos[4][2];    //coordonnées des 4 blocs de la pièce dans le carré 4x4
    Forme shape;
};

#endif // PIECE_H
