#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class Piece
{
public:

    Piece();
    char getRow() const {return Row;}
    char getCol() const {return Column;}
    char getType() const {return Type;}
    char& getType() {return Type;}
    int getPos_X() const {return pos_x;}
    int getPos_Y() const {return pos_y;}
    void setPos_X(int x) {pos_x = x;}
    void setPos_Y(int y) {pos_y = y;}
    char setType();
    void setRow(int i);
    void setCol(int j);
    void movePiece(Piece& next);
    double getPoint() const;

private:
    char Column,Row,Type;
    int pos_x,pos_y;
};
#endif