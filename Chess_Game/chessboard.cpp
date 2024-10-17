#include <iostream>
#include <vector>
#include <cctype>
#include <cmath>
#include <cstdlib> // rand func
#include <string>
#include <fstream>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

Board::Board() : piece(8,vector<Piece>(8))
{
    int i,j;
    for(i=0; i<piece.size(); ++i)
    {
        for(j=0;j<piece[i].size();++j)
        {
            piece[i][j].setRow(i);
            piece[i][j].setCol(j);
            piece[i][j].setPos_X(j);
            piece[i][j].setPos_Y(i);
            if(i<2)
            {
                piece[i][j].getType() = piece[i][j].setType();
                
            }
            else if(i<6)
            {
                piece[i][j].getType() = piece[i][j].setType();
            }
            else
            {
                piece[i][j].getType() = toupper(piece[i][j].setType());
            }
        }
    }
}

ostream& operator<<(ostream& out,const Board& main)
{
    for(int i=0;i<8;++i)
    {
        out << 8-i << " | ";
        for(int j=0;j<8;++j)
        {
            out << main.piece[i][j].getType() << "  ";
        }
        out << endl;
    }
    out << "    "; for(int i=0;i<22;++i) out << "-";
    out << "\n    ";
    for(int i=0;i<8;++i) out << static_cast<char>('a'+i) << "  ";
    out << "\n" << endl;
    return out;
}

istream& operator>>(istream& in,Board& main)
{
    char temp; int flag;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            flag = 1;
            while(flag == 1)
            {
                in >> temp;
                if(temp == '.' || temp == 'p' || temp == 'r' || temp == 'n' || temp == 'b' || temp == 'q' || temp == 'k' || temp == 'P' || temp == 'R' || temp == 'N' || temp == 'B' || temp == 'Q' || temp == 'K')
                {
                    main.piece[i][j].getType() = temp;
                    flag = 0;
                }
            }
        }
    }
    return in;
}

bool Board::checkLegal(const Piece& initial,const Piece& next) const
{
    int i= initial.getPos_Y(), j= initial.getPos_X();
    switch(initial.getType())
    {

    case 'p':
        if(initial.getCol() == next.getCol())
        {
            if(initial.getRow() == next.getRow()+2 && piece[next.getPos_Y()-1][next.getPos_X()].getType() == '.' && next.getType() == '.' && initial.getRow() == '7') return true;
            if(initial.getRow() == next.getRow()+1 && next.getType() == '.') return true;
        }
        else if(initial.getCol() == next.getCol()+1 || initial.getCol() == next.getCol()-1)
        {
            if(initial.getRow() == next.getRow()+1 && next.getType() != '.' && isupper(next.getType())) return true;
        }
        return false;
        break;

    case 'P':
        if(initial.getCol() == next.getCol())
        {
            if(initial.getRow() == next.getRow()-2 && piece[next.getPos_Y()+1][next.getPos_X()].getType() == '.' && next.getType() == '.' && initial.getRow() == '2') return true;
            if(initial.getRow() == next.getRow()-1 && next.getType() == '.') return true;
        }
        else if(initial.getCol() == next.getCol()+1 || initial.getCol() == next.getCol()-1)
        {
            if(initial.getRow() == next.getRow()-1 && next.getType() != '.' && islower(next.getType())) return true;
        }
        return false;
        break;
    case 'r':
    case 'R':
        if(initial.getCol() == next.getCol())
        {
            for(int a=1;a<abs(next.getRow() - initial.getRow());++a)
            {
                if(next.getRow() > initial.getRow())
                {
                    if(piece[i-a][j].getType() != '.') return false;
                }
                else
                {
                    if(piece[i+a][j].getType() != '.') return false;
                }
            }
        }
        else if(initial.getRow() == next.getRow())
        {
            for(int a=1;a<abs(next.getCol() - initial.getCol());++a)
            {
                if(next.getCol() > initial.getCol())
                {
                    if(piece[i][j+a].getType() != '.') return false;
                }
                else
                {
                    if(piece[i][j-a].getType() != '.') return false;
                }
            }
        }
        else return false;
        if(next.getType() == '.') return true;
        else
        {
            if(islower(next.getType()) && isupper(initial.getType())) return true;
            if(isupper(next.getType()) && islower(initial.getType())) return true;
        }
        return false;
        break;

    case 'n':
    case 'N':
        if(initial.getRow() == next.getRow()+1 ||initial.getRow() == next.getRow()-1)
        {
            if(initial.getCol() != next.getCol()+2 && initial.getCol() != next.getCol()-2) return false;
        }
        else if(initial.getRow() == next.getRow()+2 ||initial.getRow() == next.getRow()-2)
        {
            if(initial.getCol() != next.getCol()+1 && initial.getCol() != next.getCol()-1) return false;
        }
        else return false;
        if(next.getType() == '.') return true;
        else
        {
            if(islower(next.getType()) && isupper(initial.getType())) return true;
            if(isupper(next.getType()) && islower(initial.getType())) return true;
        }
        return false;
        break;

    case 'b':
    case 'B':
        if(initial.getRow() != next.getRow() && initial.getCol() != next.getCol())
        {
            if(abs(initial.getRow()-next.getRow()) != abs(initial.getCol() - next.getCol())) return false;
            else
            {
                for(int a=1;a<abs(next.getRow() - initial.getRow());++a)
                {
                    if(next.getCol() > initial.getCol())
                    {
                        if(next.getRow() > initial.getRow())
                        {
                            if(piece[i-a][j+a].getType() != '.') return false;
                        }
                        else
                        {
                            if(piece[i+a][j+a].getType() != '.') return false;
                        }
                    }
                    else
                    {
                        if(next.getRow() > initial.getRow())
                        {
                            if(piece[i-a][j-a].getType() != '.') return false;
                        }
                        else
                        {
                            if(piece[i+a][j-a].getType() != '.') return false;
                        }
                    }
                }
            }
        }
        else return false;
        if(next.getType() == '.') return true;
        else
        {
            if(islower(next.getType()) && isupper(initial.getType())) return true;
            if(isupper(next.getType()) && islower(initial.getType())) return true;
        }
        return false;
        break;

    case 'q':
    case 'Q':
        if(initial.getCol() == next.getCol())
        {
            for(int a=1;a<abs(next.getRow() - initial.getRow());++a)
            {
                if(next.getRow() > initial.getRow())
                {
                    if(piece[i-a][j].getType() != '.') return false;
                }
                else
                {
                    if(piece[i+a][j].getType() != '.') return false;
                }
            }
        }
        else if(initial.getRow() == next.getRow())
        {
            for(int a=1;a<abs(next.getCol() - initial.getCol());++a)
            {
                if(next.getCol() > initial.getCol())
                {
                    if(piece[i][j+a].getType() != '.') return false;
                }
                else
                {
                    if(piece[i][j-a].getType() != '.') return false;
                }
            }
        }
        else if(abs(initial.getRow() - next.getRow()) == abs(initial.getCol() - next.getCol()))
        {
            for(int a=1;a<abs(next.getRow() - initial.getRow());++a)
            {
                if(next.getCol() > initial.getCol())
                {
                    if(next.getRow() > initial.getRow())
                    {
                        if(piece[i-a][j+a].getType() != '.') return false;
                    }
                    else
                    {
                        if(piece[i+a][j+a].getType() != '.') return false;
                    }
                }
                else
                {
                    if(next.getRow() > initial.getRow())
                    {
                        if(piece[i-a][j-a].getType() != '.') return false;
                    }
                    else
                    {
                        if(piece[i+a][j-a].getType() != '.') return false;
                    }
                }
            }
        }
        else return false;
        if(next.getType() == '.') return true;
        else
        {
            if(islower(next.getType()) && isupper(initial.getType())) return true;
            if(isupper(next.getType()) && islower(initial.getType())) return true;
        }
        return false;
        break;

    case 'k':
    case 'K':
        if((initial.getRow() == next.getRow() && abs(initial.getCol()-next.getCol()) == 1) || (initial.getCol() == next.getCol() && abs(initial.getRow()-next.getRow()) == 1) || (abs(initial.getCol() -next.getCol()) == 1 && abs(initial.getRow()-next.getRow()) == 1))
        {
            Board temp(*this); temp.piece[i][j].movePiece(temp.piece[next.getPos_Y()][next.getPos_X()]);
            if(temp.checkking(temp.piece[next.getPos_Y()][next.getPos_X()], temp.piece[next.getPos_Y()][next.getPos_X()].getType() == 'K' ? 'W' : 'B')) return false;
        }
        else return false;
        if(next.getType() == '.') return true;
        else
        {
            if(islower(next.getType()) && isupper(initial.getType())) return true;
            if(isupper(next.getType()) && islower(initial.getType())) return true;
        }
        return false;
        break;

    default :   return false;
    }
}

void Board::readMove(char player)
{
    int flag =0,i,j,i_n,j_n;
    string a;
    do
    {
        cout << "Enter your move: ";
        cin >> a;
        if(a == "suggest")
        {
            double first_score = score(player == 'W' ? 'B' : 'W');
            a.resize(4);
            a = suggest(player,first_score);
            cout << "Suggested move is : "<< a[0] << a[1] << a[2] << a[3] << endl;
            cout << "Enter your move: ";
            cin >> a;
        }
        if(a.size() == 4)
        {
            char a1,a2,a3,a4;
            a1= a[0]; a2= a[1]; a3= a[2]; a4= a[3];
            if(a1 < 'a' || a1 > 'h' || a2 < '1' || a2 > '8' || a3 < 'a' || a3 > 'h' || a4 < '1' || a4 > '8' || (a1 == a3 && a2==a4))
            {
                cout << "Invalid input! Try again." << endl;
                flag = 1;
            }
            else
            {
                i= abs((a2 -'0') - 8);  i_n=abs((a4 - '0')-8);
                j= a1 - 'a';            j_n= a3 - 'a';
                Piece &initial= piece[i][j], &next= piece[i_n][j_n];
                if(checkLegal(initial,next) && ((player == 'W' && isupper(initial.getType())) || (player == 'B' && islower(initial.getType()))))
                {
                    Board temp(*this); temp.piece[i][j].movePiece(temp.piece[i_n][j_n]);
                    if(temp.checkking(temp.findking(player),player))
                    {   cout << "King is checked! " << endl;
                        flag = 1;
                    }
                    else
                    {
                        initial.movePiece(next);
                        flag = 0;
                    }
                }
                else
                {
                    cout << "Illegal Move! Try Again."<< endl;
                    flag = 1;
                }
            }
        }
        else
        {
            cout << "Invalid input! Try again." << endl;
            flag = 1;
        } 
    }while(flag == 1); 
}

bool Board::checkking(const Piece& king,char player) const
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if((player == 'W' && islower(piece[i][j].getType())) || (player == 'B' && isupper(piece[i][j].getType())))
            {
                if(checkLegal(piece[i][j],king))  return true;
            }
        }
    }
    return false;
}

Piece Board::findking(char player) const
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(player == 'W' && piece[i][j].getType() == 'K') return piece[i][j];
            if(player == 'B' && piece[i][j].getType() == 'k') return piece[i][j];
        }
    }
    cout << "Error occurred While finding the king "<< endl;
    exit(-1);
}

double Board::score(char player) const
{
    double total=0;
    int flag1,flag2;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if((isupper(piece[i][j].getType()) && player == 'W') || (islower(piece[i][j].getType()) && player == 'B'))
            {
                flag1 =1; flag2 =1;
                for(int k=0;k<8;++k)
                {
                    for(int l=0;l<8;++l)
                    {
                        if(piece[i][j].getType() != piece[k][l].getType() && flag2 == 1)
                        {
                            if(checkLegal(piece[k][l],piece[i][j]))
                            {
                                total += piece[i][j].getPoint()/2;
                                flag1 =0; flag2 =0;
                            }
                        }
                    }
                }
                if(flag1 == 1)
                {
                    total += piece[i][j].getPoint();
                    flag2 =0;
                }
            }
        }
    }
    return total;
}

string Board::suggest(char player,double best_score)
{
    Board temp(*this);  string move;
    double temp_score,first_score; Piece init,final;
    first_score = best_score;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if((isupper(piece[i][j].getType()) && player == 'W') || (islower(piece[i][j].getType()) && player == 'B'))
            {
                for(int k=0;k<8;++k)
                {
                    for(int l=0;l<8;++l)
                    {
                        if(piece[i][j].getType() != piece[k][l].getType() && checkLegal(piece[i][j],piece[k][l]))
                        {
                            temp.piece[i][j].movePiece(temp.piece[k][l]);
                            temp_score = temp.score(player == 'W' ? 'B' : 'W');
                            if(!(temp.checkking(temp.findking(player),player)))
                            {
                                if(temp_score < best_score)
                                {
                                    best_score = temp_score;
                                    init = piece[i][j];
                                    final = piece[k][l];
                                }
                            }
                            temp = *this;
                        }
                    }
                }
            }
        }
    }
    if(first_score == best_score)
    {
        int i,j,i_n,j_n,flag = 1;
        srand(time(0));
        do
        {
            j= rand()%8; j_n= rand()%8;
            i= rand()%8; i_n= rand()%8;
            if(checkLegal(piece[i][j],piece[i_n][j_n]) && ((player == 'W' && isupper(piece[i][j].getType())) || (player == 'B' && islower(piece[i][j].getType()))))
            {
                temp.piece[i][j].movePiece(temp.piece[i_n][j_n]);
                if(checkking(temp.findking(player),player)) flag = 1;
                else
                {
                    flag = 0;
                    move += piece[i][j].getCol(); move += piece[i][j].getRow(); move += piece[i_n][j_n].getCol(); move += piece[i_n][j_n].getRow();
                }
                temp = *this;
            }

        }while(flag == 1);
    }
    else  move = {init.getCol(),init.getRow(),final.getCol(),final.getRow()};
    return move;
}

bool Board::isOver(char player) const
{
    Piece king = findking(player);
    if(checkking(king,player))
    {
        for(int i=0; i<8;++i)
        {
            for(int j=0;j<8;++j)
            {
                for(int i_n=0;i_n<8;++i_n)
                {
                    for(int j_n =0;j_n<8;++j_n)
                    {
                        if(checkLegal(piece[i][j],piece[i_n][j_n]) && ((player == 'W' && isupper(piece[i][j].getType())) || (player == 'B' && islower(piece[i][j].getType()))))
                        {
                            Board temp(*this);
                            temp.piece[i][j].movePiece(temp.piece[i_n][j_n]);
                            if(!temp.checkking(temp.findking(player),player))  return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

void Board::savetofile(string filename)
{
    ofstream outstream;
    cout << "Board is saving to the file : "<< filename << endl;
    outstream.open(filename);
    if(!outstream.is_open())
    {
        cout << "Error while opening the file! "<< endl;
        exit(-1);
    }
    outstream << *this;
    cout << "Board succesfully saved to the file : "<< filename << endl;
    outstream.close();

}

void Board::loadfromfile(string filename)
{
    ifstream instream;
    cout << "Board is loading from a file : "<< filename << endl;
    instream.open(filename);
    if(!instream.is_open())
    {
        cout << "Error while opening the file! "<< endl;
        exit(-1);
    }
    instream >> *this;
    cout << "Board succesfully loaded from a file : "<< filename << endl;
    instream.close();
}