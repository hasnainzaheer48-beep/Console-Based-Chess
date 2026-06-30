#include<iostream>
#include"MoveValidator.h"
#include"GameState.h"

using namespace std;

bool MoveValidator::IsValid(char crtTurn, int srcRow, int srcCol, int dstRow, int dstCol, Board& board , bool ShowError)
{
	Piece* piece = board.getPiece(srcRow, srcCol);
	
	if (piece == nullptr) //check for empty source
	{
		
		

		
		return false;
	}

	if (srcRow == dstRow && srcCol == dstCol) //Moving to same spot
	{
		
			
		
		return false;

	}


	if (crtTurn != piece->getColor())            //check if piece belong to player
	{

		
			

		
		return false;

	}

	Piece* dstPiece = board.getPiece(dstRow, dstCol);

	if (dstPiece != nullptr && dstPiece->getColor() == crtTurn)         //check if piece at dst does not belong to the player 
	{
		
		
			

		
		return false;


	}
	

	if (!(piece->isValidMove(srcRow,srcCol,dstRow,dstCol,board)))
	{
		         //checks move of specific piece

		
		

		 
		

		return false;
	}

	

	//I HAVE TO ADD RETURN TRUE BY END 

	return true;
}