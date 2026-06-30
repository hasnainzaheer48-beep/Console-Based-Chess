#include"King.h"

King::King(char color, char symbol) : Piece(color, symbol)
{

}


bool King::isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board)
{
	int rowDiff = dstRow - srcRow;
	int colDiff = dstCol - srcCol;

	if (rowDiff < 0)
		rowDiff = -1 * rowDiff;
	if (colDiff < 0)
		colDiff = -1 * colDiff;

	if (rowDiff <= 1 && colDiff <= 1)
		return true;


	
	return false;
}