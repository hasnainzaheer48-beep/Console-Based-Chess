#include"Rook.h"

Rook::Rook(char color, char symbol) : Piece(color, symbol)
{

}

bool Rook::isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board)
{

	if (srcRow != dstRow && srcCol != dstCol)
		return false;
	if ((srcRow == dstRow) && (srcCol != dstCol))  //horizontal moving
	{
		//moving right
		if (srcCol < dstCol)
		{
			for (int r = srcCol + 1; r < dstCol; r++)
			{
				if (board.getPiece(srcRow,r) != nullptr)
					return false;
			}
		}
		else     //moving left
		{
			for (int r = srcCol - 1; r > dstCol; r--)
			{
				if (board.getPiece(srcRow,r) != nullptr)
					return false;
			}
		}
	}
	
	else if ((srcRow != dstRow) && (srcCol == dstCol))   //Vertical moving
	{
		//Moving Up
		if (srcRow > dstRow)
		{
			for (int c = srcRow - 1; c > dstRow; c--)
			{
				if (board.getPiece(c,srcCol) != nullptr)
					return false;
			}
		}

		//Moving Down
		else if (srcRow < dstRow)
		{
			for (int c = srcRow + 1; c < dstRow; c++)
			{
				if (board.getPiece(c,srcCol) != nullptr)
					return false;
			}
		}

	}


	return true;
}