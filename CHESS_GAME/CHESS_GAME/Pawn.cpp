#include"Pawn.h"

Pawn::Pawn(char color, char symbol) : Piece(color, symbol)
{
	
}

bool Pawn::isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board)
{
	//check color
	Piece* piece = board.getPiece(srcRow, srcCol);
	char p = piece->getColor();
	int mv;
	if (p == 'W')
		mv = -1;
	else
		mv = +1;

	if ((dstRow == srcRow + mv) && (dstCol == srcCol))
	{
		if ( board.getPiece(dstRow,dstCol) == nullptr)
			return true;
	}
	
	if ((p == 'W' && srcRow == 6) || (p == 'B' && srcRow == 1)) //agar true means its the first move
	{
		if (((dstRow == srcRow + (2 * mv)) && (dstCol == srcCol)))
			if ( board.getPiece(dstRow,dstCol) == nullptr && board.getPiece(srcRow + mv, srcCol) == nullptr)   //pehli condintion to check jahan jana woh free or not
				return true;																//Next checking agar src aur dst kay beechwala empty ya ni 
	}

	
	//Diagonal Capture
	if (board.getPiece(dstRow, dstCol) != nullptr)           //Destination is not empty
	{
		Piece* dstPiece = board.getPiece(dstRow, dstCol);
		if (p != dstPiece->getColor())                       //Piece at Destination is of opponent
		{
			if (((dstRow == srcRow + mv) && (dstCol == srcCol + mv)) || ((dstRow == srcRow + mv) && (dstCol == srcCol - mv)))
				return true;
		}
	}


	

	return false;
}