#pragma once
#include"Piece.h"
#include<string>




class Board;

class MoveValidator
{
public: 
	
	bool IsValid(char crtTurn, int srcRow, int srcCol, int dstRow, int dstCol, Board& board , bool ShowError);
};
