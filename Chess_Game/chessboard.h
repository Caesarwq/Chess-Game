#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include "chesspiece.h"

using namespace std;

class Board
{
public:

    Board();
    friend ostream& operator<<(ostream& out,const Board& main);
    friend istream& operator>>(istream& in,Board& main);
    void readMove(char player);
    bool checkLegal(const Piece& initial,const Piece& next) const;
    bool isOver(char player) const;
    Piece findking(char player) const;
    bool checkking(const Piece& king,char player) const;
    double score(char player) const;
    string suggest(char player,double best_score);
    void savetofile(string filename);
    void loadfromfile(string filename);

private:
    vector<vector<Piece>> piece;
};
#endif