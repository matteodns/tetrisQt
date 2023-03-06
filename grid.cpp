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

// Returns the width of each square in the grid
int Grid::squareWidth()
{
    return contentsRect().width()/gridWidth;
}

//Returns the height of each square in the grid
int Grid::squareHeight()
{
    return contentsRect().height()/gridHeight;
}

// Creates a new random piece for the grid
bool Grid::tryNewRandPiece()
{

    Forme newShape(Forme(rand()%7+1));
    Piece *newPiece = new Piece(newShape);

    posCurPiece[0] = gridWidth/2-1;
    posCurPiece[1] = 0;  //à modifier si nouvelles piece (avec un ymin != 0)

    for (int i(0); i<4; i++){

        // Get the x and y coordinates of the current block
        int yPiece(newPiece->getPosY(i));
        int xPiece(newPiece->getPosX(i));
        
        // Add the coordinates of the piece to the position of the piece
        yPiece+=posCurPiece[1];
        xPiece+=posCurPiece[0];
        
        // Check if the block is overlapping with an existing block
        if (grille[yPiece][xPiece] != noShape){
        
            // Delete the new piece if it is overlapping
            delete newPiece;
        
            // Set the game to finished
            isFinished = true;
        
            // Stop the timer
            timer.stop();
        
            // Update the game, fin de la partie
            update(); 
        
            // Return false
            return false;
        
        }
        
          

    }

    curPiece=newPiece;

    update();

    return true;

}

// This function tries to rotate the current piece and checks if it is possible
bool Grid::tryRotate(Piece *newPiece)
{
    // Iterate through each of the 4 blocks in the piece
    for (int i(0); i<4; i++){

        // Get the x and y coordinates of the block
        int yPiece(newPiece->getPosY(i));
        int xPiece(newPiece->getPosX(i));

        // Add the current position of the piece to the coordinates
        yPiece += posCurPiece[1];
        xPiece += posCurPiece[0];

        // Check if the new position is valid
        // If it is not, delete the new piece and return false
        if (yPiece<0 || yPiece>=gridHeight || xPiece<0 || xPiece>=gridWidth || grille[yPiece][xPiece] != noShape){
            delete newPiece;
            return false;
        }
    }

    // If the rotation was successful, set the current piece to the new piece
    curPiece=newPiece;

    // Update the grid
    update();

    // Return true to indicate success
    return true;
}

// This function tries to move the current piece by the given coordinates
bool Grid::tryMove(int newX, int newY)
{
    // Iterate through all pieces of the current piece
    for (int i(0); i<4; i++){
        int yPiece(curPiece->getPosY(i));
        int xPiece(curPiece->getPosX(i));

        // Calculate the new position
        yPiece += newY;
        xPiece += newX;

        Forme nvPos = grille[yPiece][xPiece];

        // Check if the new position is valid
        if (yPiece<0 || yPiece>=gridHeight || xPiece<0 || xPiece>=gridWidth || nvPos != noShape){
            return false;
        }
    }

    // Update the current piece's position
    posCurPiece[0]=newX;
    posCurPiece[1]=newY;

    update();

    return true;
}


// Attemps to move the current piece down. If it is successful, it returns True, otherwise it places the piece on the grid and updates the game state
bool Grid::tryMoveDown()
{   
    // Check if the piece can be moved down
    if(!tryMove(posCurPiece[0],posCurPiece[1]+1))
    {
        for (int i(0); i<4; i++){
            // Place the piece on the grid
            grille[curPiece->getPosY(i)+posCurPiece[1]][curPiece->getPosX(i)+posCurPiece[0]] = curPiece->getShape();
        }
        // Increment the number of pieces dropped
        pieceDropped+=1;

        // Remove any full lines
        removeLines();

        // Updates the level every 15 pieces dropped
        if (pieceDropped%15==0) level+=1;
        emit levelChanged(level);

        // Updates the timer interval
        timer.setInterval(1000-700*(level-1)/10);

        // Gives a new random piece
        tryNewRandPiece();

        // indicates that the piece coud not be moved down
        return false;
    }
    
    // Indicates that the piece was successfully moved down
    return true;
}

// Start the game
void Grid::start()
{
    // Initialize score, level, pieces dropped and lines removed
    score = 0;
    level = 1;
    pieceDropped = 0;
    linesRemoved = 0;

    // Start the timer
    timer.start(1000);

    // Try to generate a new random piece
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
    // Checks if the game is finished. If it is, the key press event is passed to the parent widget
    if (isFinished){
        QWidget::keyPressEvent(event);
        return;
    }

    // Checks which key was pressed and performs the appropriate action
    switch (event->key()) {
    
    // Moves the current piece one cell to the left
    case Qt::Key_Left:
        tryMove(posCurPiece[0]-1, posCurPiece[1]);
        break;
    
    // Moves the current piece one cell to the right
    case Qt::Key_Right:
        tryMove(posCurPiece[0]+1, posCurPiece[1]);
        break;

    // Rotates the current piece to the left
    case Qt::Key_Up:
        tryRotate(curPiece->rotateLeft());
        break;

    // Rotates the current piece to the right
    case Qt::Key_Down:
        tryRotate(curPiece->rotateRight());
        break;

    // Tries to move the current piece down
    case Qt::Key_Space:
        tryMoveDown();
        break;

    // Passes the key press event to the parent widget
    default:
        QWidget::keyPressEvent(event);
    }
}

void Grid::removeLines()
{
    int nowRemoved(0);

    // Loop through each row in the grid
    for (int i(0); i<gridHeight; i++){
        // Check if the line is full
        bool lineFull(true);
        for (int j(0); j<gridWidth; j++)
        {
            if (grille[i][j]==0){
                lineFull=false;
                break;
            }
        }

        // If the line is full, shift all elements above it down one row 
        if (lineFull)
        {
            for (int k(i);k>0; k--){
                for (int j(0); j<gridWidth; j++){
                    grille[k][j] = grille[k-1][j];
                }
            }
        
            nowRemoved+=1;
            linesRemoved+=1;
        }
        
    }

    // Calculate the score based on the number of lines removed and the current level
    int initScore(0);

    if (nowRemoved==0) initScore = 0;
    if (nowRemoved==1) initScore = 40;
    if (nowRemoved==2) initScore = 100;
    if (nowRemoved==3) initScore = 300;
    if (nowRemoved==4) initScore = 1200;

    score += initScore*level;
    emit scoreChanged(score);


    // Update the grid
    update();
}

























