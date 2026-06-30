#pragma once
#include"Piece.h"
#include"Board.h"
class King : public Piece
{
public:
	King(char color, char symbol);
	bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board);

};