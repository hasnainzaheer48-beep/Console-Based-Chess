#include"Bishop.h"
#include<cmath>

Bishop::Bishop(char color, char symbol) : Piece(color, symbol)
{
	

}

bool Bishop::isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board)
{
	//First make sure it doesnt move horizontal or vertical
	if (srcRow == dstRow || srcCol == dstCol)
		return false;

	if (abs(dstRow - srcRow) != abs(dstCol - srcCol))
		return false;
	//Four parts 
	// Moving from Top to Bottom Left to Right
	if (srcRow < dstRow && srcCol < dstCol)
	{
		for (int i = 1; i < (dstRow - srcRow);i++)
		{
			if (board.getPiece(srcRow + i,srcCol + i) != nullptr)
				return false;
		}
	}
	// Moving from Top to Btoom Right to Left
	if (srcRow< dstRow && srcCol > dstCol)
	{
		for (int i = 1; i <(dstRow - srcRow); i++ )
		{
			if (board.getPiece(srcRow + i,srcCol - i) != nullptr)
				return false;
		}
	}
	// Moving from Bottom to Top Left to Right
	if (srcRow > dstRow && srcCol < dstCol)
	{
		for (int i = 1; i < (dstCol - srcCol); i++)
		{
			if (board.getPiece(srcRow - i,srcCol + i) != nullptr)
				return false;
		}
	}
	// Moving from Bottom to Top Right to Left
	if (srcRow > dstRow && srcCol > dstCol)
	{
		for (int i = 1; i < (srcRow - dstRow); i++)
		{
			if (board.getPiece(srcRow - i,srcCol - i) != nullptr)
				return false;
		}
	}


	return true;
}

