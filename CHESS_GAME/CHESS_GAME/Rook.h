#pragma once
#include"Piece.h"
#include"Board.h"
class Rook : public Piece
{
public:
	Rook(char color, char symbol);
	bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board);
};