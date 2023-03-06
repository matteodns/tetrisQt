#ifndef PIECE_H
#define PIECE_H

enum Forme{noShape, iShape, oShape, tShape, lShape, jShape, zShape, sShape};

class Piece
{
public:

    // Constructor for creating a new Piece object with a given shape.
    // If no shape is specified, the default is 'noShape'.
    Piece(Forme newShape = noShape);
    
    // Rotate the piece to the right.
    Piece* rotateRight();
    
    // Rotate the piece to the left.
    Piece* rotateLeft();
    
    // Get the x-coordinate of a block at a given index.
    int getPosX(int index);
    
    // Get the y-coordinate of a block at a given index.
    int getPosY(int index);
    
    // Get the shape of the piece.
    Forme getShape();

private:

    // Set the x-coordinate of a block at a given index.
    void setX(int index, int x);
    
    // Set the y-coordinate of a block at a given index.
    void setY(int index, int y);
    
    // Array containing the coordinates of the 4 blocks of the piece in the 4x4 square.
    int pos[4][2];
    
    // Shape of the piece.
    Forme shape;
    
};

#endif // PIECE_H
