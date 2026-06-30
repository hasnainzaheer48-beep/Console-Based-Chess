#include"Knight.h"

Knight::Knight(char color, char symbol) : Piece(color, symbol)
{

}

bool Knight::isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board)
{
	int rowDiff = dstRow - srcRow;
	int colDiff = dstCol - srcCol;

	if ((rowDiff == 2 || rowDiff == -2) && (colDiff == 1 || colDiff == -1))
		return true;
	if ((rowDiff == 1 || rowDiff == -1) && (colDiff == 2 || colDiff == -2))
		return true;



	return false;
		
}
