#include <iostream>
#include "chesspiece.h"

using namespace std;

Piece::Piece() : Column(' '), Row(' '),Type(' '), pos_x(0), pos_y(0) {}

char Piece::setType()
{
    if(Row == '7' || Row == '2') return 'p';
    else if(Row == '1' || Row == '8')
    {
        if(Column == 'a' || Column == 'h') return 'r';
        else if(Column == 'b' || Column == 'g') return 'n';
        else if(Column == 'c' || Column == 'f') return 'b';
        else if(Column == 'd') return 'q';
        else return 'k';
    }
    else return '.';
}

void Piece::setCol(int j)
{
    switch(j%8)
    {
        case 0 : Column = 'a';
        break;
        case 1 : Column = 'b';
        break;
        case 2 : Column = 'c';
        break;
        case 3 : Column = 'd';
        break;
        case 4 : Column = 'e';
        break;
        case 5 : Column = 'f';
        break;
        case 6 : Column = 'g';
        break;
        case 7 : Column = 'h';
        break;
    }
}

void Piece::setRow(int i)
{
    if(i == 0) Row = '8';
    else if(i == 1) Row = '7';
    else if(i == 2) Row = '6';
    else if(i == 3) Row = '5';
    else if(i == 4) Row = '4';
    else if(i == 5) Row = '3';
    else if(i == 6) Row = '2';
    else Row = '1';
}

void Piece::movePiece(Piece& next)
{
    next.Type = Type;
    Type = '.';
}

double Piece::getPoint() const
{
    switch(getType())
    {
        case 'p':
        case 'P':
            return 1.00;
        break;

        case 'r':
        case 'R':
            return 5.00;
        break;

        case 'n':
        case 'N':
            return 3.00;
        break;

        case 'b':
        case 'B':
            return 3.00;
        break;

        case 'q':
        case 'Q':
            return 9.00;
        break;

        case 'k':
        case 'K':
            return 100.00;
        break;

        default:
            cout << "Error happened while getting point! "<<endl;
            exit(-1);
    }
}