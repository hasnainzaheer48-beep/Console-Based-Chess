#pragma once
#include"Piece.h"
#include"Board.h"

class Bishop : public Piece
{
public:
	Bishop(char color, char symbol);
	bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board);
};