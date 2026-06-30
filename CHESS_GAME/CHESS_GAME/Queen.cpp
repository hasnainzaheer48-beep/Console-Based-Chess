#include"Queen.h"
#include"Rook.h"
#include"Bishop.h"

Queen::Queen(char color, char symbol) : Piece(color, symbol)
{

}


bool Queen::isValidMove(int srcRow, int srcCol, int dstRow, int dstCol, Board& board)
{
	Piece* piece = board.getPiece(srcRow,srcCol);
	char c = piece->getColor();
	Bishop p(c, 'B');
	Rook p1(c, 'R');

	return (p.isValidMove(srcRow, srcCol, dstRow, dstCol, board) || p1.isValidMove(srcRow, srcCol, dstRow, dstCol, board));
		
		

}