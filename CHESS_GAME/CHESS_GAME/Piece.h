#pragma once

class Board;
class Piece {

protected: 
	char color;
	char symbol;

public:
	Piece(char color, char symbol);
	char getColor();
	char getSymbol();
	virtual bool isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board) = 0;
	//virtual ~Piece();

};