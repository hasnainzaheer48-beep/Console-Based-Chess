#pragma once
#include"Piece.h"
#include"Board.h"

class Queen : public Piece
{
public:
	Queen(char color,char symbol);
	bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board);
};