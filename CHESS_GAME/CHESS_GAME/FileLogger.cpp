#include"FileLogger.h"

FileLogger::FileLogger()
{
	moveNumber = 1;

	file.open("ChessLogger.txt");

	if (file.is_open())
	{
		file << "----------------------CHESS GAME LOGGER-----------------------";

	}


}


void FileLogger::logMove(char player, char piece, int srcRow, int srcCol, int dstRow,
						int dstCol, bool isCapture, bool isEnPassant, bool isCastling,
						bool isPromotion, bool isCheck)
{
	file << "\n===========================================================";
	file << "\nMove " << moveNumber << ": ";
	moveNumber++;
	if (player == 'W')
	{
		file << "White";
	}

	if (player == 'B')
	{
		file << "Black";

	}

	switch (piece)
	{
	case 'P':
	case 'p':
	 file << " Pawn "; break;
	case 'K':
	case 'k':
		file << " King "; break;
	case 'N':
	case 'n':
		file << " Knight "; break;
	case 'B':
	case 'b':
		file << " Bishop "; break;
	case 'R':
	case 'r':
		file << " Rook "; break;
	case 'Q':
	case 'q':
		file << " Queen "; break;

	}

	char sourceCol = 'a' + srcCol;
	char destCol = 'a' + dstCol;

	file << sourceCol << (8 - srcRow) << " -> " << destCol << (8 - dstRow);

	if (isCapture)
		file << "  [ Piece Captured ]";

	if (isEnPassant)
		file << "  [ EnPassant ]";

	if (isCastling)
		file << "  [ Castling ]";

	if (isPromotion)
		file << "  [ Pawn Promotion ]";

	if (isCheck)
		file << "  [ King in Check ]";


	
		

	
	file << "\n===========================================================";

}


void FileLogger::logResignation(char color)
{
	if (color == 'W')
		file << "\n==============WHITE RESIGNS :: BLACK WINS======================";
	if (color == 'B')
		file << "\n =================BLACK RESIGN :: WHITE WINS===================== ";
}


void FileLogger::logCheckmate(char color)
{
		
		if (color == 'W')
			file << "\n==========WHITE WINS BY CHECKMATE==============";
		if (color == 'B')
			file << "\n==========BLACK WINS BY CHECKMATE==============";

	
}
void FileLogger::logStalemate(char color)
{
	file << "\n ==============[ Stalemate ]===================";
}