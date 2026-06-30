#pragma once
#include"Piece.h"
#include<windows.h>

class Board {
private:
    Piece*  grid[8][8];
public:
    Board();
    Board(const Board& board);
    ~Board();
    void initialize();
    void print();
    Piece* getPiece(int row, int col);
    void setPiece(int row, int col, Piece* piece);
    bool movePiece(int srcRow, int srcCol, int dstRow, int dstCol);
    void setColor(int color);
   
};