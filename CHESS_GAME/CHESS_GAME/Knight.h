#pragma once
#include"Piece.h"
#include"Board.h"

class Knight : public Piece
{
public:
	Knight(char color, char symbol);
	bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board);
};