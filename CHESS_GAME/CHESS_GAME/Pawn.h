#pragma once
#include"Piece.h"
#include"Board.h"
class Pawn : public Piece
{
public:
	Pawn(char color, char symbol);
	bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board);

};