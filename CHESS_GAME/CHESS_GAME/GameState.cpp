#include<iostream>
#include"GameState.h"
#include"MoveValidator.h"
#include"Queen.h"
#include"Rook.h"
#include"Bishop.h"
#include"Knight.h"

using namespace std;


GameState::GameState()
{
	 whiteKingMoved = false;
	 blackKingMoved = false;
	 whiteRookAMoved = false;
	 whiteRookHMoved = false;
	 blackRookAMoved = false;
	 blackRookHMoved = false;
	
	 
}

void GameState::startGame()
{
	board.initialize();
	currentTurn = 'W';

	while (true)
	{
		int sourceRow, destRow;
		char sourceCol, destCol;

		cout << endl;
		cout << "\n==========================================\n";
		board.print();
		cout << "\n==========================================";

		cout << (currentTurn == 'W'
			? "\n======== White's Turn ========\n": "\n======== Black's Turn ========\n");

		cout << "\n Enter Source(00 to resign): ";
		cin >> sourceCol >> sourceRow;

		cout << "\n Enter Destination(00 to resign): ";
		cin >> destCol >> destRow;

		if (sourceRow == 0 && sourceCol == '0')
		{
			log.logResignation(currentTurn);


			if (currentTurn == 'W')
			{
				cout << "\nWHITE RESIGNS:: BLACK WINS";
				break;
			}

			if (currentTurn == 'B')
			{
				cout << "\nBLACK RESIGNS :: WHITE WINS";
				break;
			}
		}



		int SrcCol = convert(sourceCol);
		int DstCol = convert(destCol);
		sourceRow = convert(sourceRow);
		destRow = convert(destRow);

		MoveValidator Valid;

		bool IsEnpassant = EnPassant(sourceRow, SrcCol, destRow, DstCol);
		bool IsCastle = Castling(sourceRow, SrcCol, destRow, DstCol);

		// Validation

		Piece* piece = board.getPiece(sourceRow, SrcCol);

		if (piece == nullptr)
		{
			cout << "\n  No piece at the selected source square!";
			continue;
		}

		if (piece->getColor() != currentTurn)
		{
			cout << "\n  You cannot move opponent's piece!";
			continue;
		}

		Piece* dstPiece = board.getPiece(destRow, DstCol);

		if (dstPiece != nullptr && dstPiece->getColor() == currentTurn)
		{
			cout << "\n  You cannot capture your own piece!";
			continue;
		}

		// normal move validation 
		bool normalValid = Valid.IsValid(currentTurn, sourceRow, SrcCol, destRow, DstCol, board, false);

		if (!IsCastle && !IsEnpassant && !normalValid)
		{
			cout << "\n  That piece cannot move like that!";
			continue;
		}

		// Simulatiom
		Board tempBoard(board);

		if (IsEnpassant)
			tempBoard.setPiece(prevDstRow, prevDstCol, nullptr);

		if (IsCastle)
		{
			if (destRow == 7 && DstCol == 6)
				tempBoard.movePiece(7, 7, 7, 5);
			else if (destRow == 7 && DstCol == 2)
				tempBoard.movePiece(7, 0, 7, 3);
			else if (destRow == 0 && DstCol == 6)
				tempBoard.movePiece(0, 7, 0, 5);
			else if (destRow == 0 && DstCol == 2)
				tempBoard.movePiece(0, 0, 0, 3);
		}

		tempBoard.movePiece(sourceRow, SrcCol, destRow, DstCol);

		//Check king
		if (isInCheck(currentTurn, tempBoard))
		{
			cout << "\n CANNOT MOVE: King would be in check.";
			continue;
		}

		// Move on Actual board
		Piece* p = board.getPiece(sourceRow, SrcCol);

		if (IsEnpassant)
			board.setPiece(prevDstRow, prevDstCol, nullptr);

		if (IsCastle)
		{
			if (destRow == 7 && DstCol == 6)
				board.movePiece(7, 7, 7, 5);
			else if (destRow == 7 && DstCol == 2)
				board.movePiece(7, 0, 7, 3);
			else if (destRow == 0 && DstCol == 6)
				board.movePiece(0, 7, 0, 5);
			else if (destRow == 0 && DstCol == 2)
				board.movePiece(0, 0, 0, 3);
		}

		bool Capture = (board.getPiece(destRow, DstCol) != nullptr) || IsEnpassant;
		
		
		board.movePiece(sourceRow, SrcCol, destRow, DstCol);

		//Update flags
		if (p != nullptr)
		{
			char sym = p->getSymbol();

			if (sym == 'K') whiteKingMoved = true;
			else if (sym == 'k') blackKingMoved = true;

			else if (sym == 'R')
			{
				if (sourceRow == 7 && SrcCol == 0) whiteRookAMoved = true;
				else if (sourceRow == 7 && SrcCol == 7) whiteRookHMoved = true;
			}
			else if (sym == 'r')
			{
				if (sourceRow == 0 && SrcCol == 0) blackRookAMoved = true;
				else if (sourceRow == 0 && SrcCol == 7) blackRookHMoved = true;
			}
		}

		//Promotion
		Piece* piece1 = board.getPiece(destRow, DstCol);
		bool promotion = false;
		if (piece1 != nullptr)
		{
			if (piece1->getSymbol() == 'P' && destRow == 0)
			{
				promotion = true;
				PawnPromotion('P', destRow, DstCol);
			}
			else if (piece1->getSymbol() == 'p' && destRow == 7)
			{
				promotion = true;
				PawnPromotion('p', destRow, DstCol);
			}
		}

		// Check and CheckMate
		char oppColor = (currentTurn == 'W') ? 'B' : 'W';
		bool InCheck = isInCheck(oppColor, board);
		bool CheckMate = isCheckmate(oppColor, board);
		bool StaleMT = isStalemate(oppColor, board);
		if (InCheck)
			cout << "\n CHECK !!";

		if (CheckMate)
		{
			board.print();
			log.logCheckmate(currentTurn);
			(currentTurn == 'W')? cout << "\n CHECKMATE! WHITE WINS!!": cout << "\n CHECKMATE! BLACK WINS!!";
			break;
		}

		if (StaleMT)
		{
			board.print();
			log.logStalemate(currentTurn);
			cout << "\n STALEMATE - DRAW";
			break;
		}

		
		prevSrcRow = sourceRow;
		prevSrcCol = SrcCol;
		prevDstRow = destRow;
		prevDstCol = DstCol;
		prevPiece = (piece1 != nullptr ? piece1->getSymbol() : '\0');



		log.logMove(currentTurn, p->getSymbol(),  sourceRow,  SrcCol, destRow,
			DstCol, Capture, IsEnpassant, IsCastle,
			promotion,  InCheck);





		switchTurn();




		cout << "\n----------------------------------------------------------------------\n";
	}

	cout << "\n\n\n\n\n";
}
void GameState::switchTurn()
{
	if (currentTurn == 'W')
		currentTurn = 'B';
	else
		currentTurn = 'W';
}

int GameState::convert(char coordinate)
{
	return coordinate - 'a';

}

int GameState::convert(int cdn)
{
	return 8 - cdn;
}


void GameState::PawnPromotion(char Symb ,int dstRow, int  dstCol)
{
	char c;
	if (Symb == 'P' && dstRow == 0)
	{

		cout << "\n Pawn Promoted:\n Q = Queen\n R = Rook\n B = Bishop\n N = Knight\n  Choose Promotion: ";
		cin >> c;
		while (c != 'Q' && c != 'R' && c != 'B' && c != 'N')
		{
			cout << "Invalid choice. Try again: ";
			cin >> c;
		}
		if (c == 'Q')
			board.setPiece(dstRow, dstCol, new Queen('W', 'Q'));
		else if(c == 'R')
			board.setPiece(dstRow, dstCol, new Rook('W', 'R'));
		else if (c == 'B')
			board.setPiece(dstRow, dstCol, new Bishop('W', 'B'));
		else if (c == 'N')
			board.setPiece(dstRow, dstCol, new Knight('W', 'N'));
		
	}

	if (Symb == 'p' && dstRow == 7)
	{

		cout << "\n Pawn Promoted:\n q = Queen\n r = Rook\n b = Bishop\n n = Knight\n  Choose Promotion: ";
		cin >> c;
		while (c != 'q' && c != 'r' && c != 'b' && c != 'n')
		{
			cout << "Invalid choice. Try again: ";
			cin >> c;
		}
		if (c == 'q')
			board.setPiece(dstRow, dstCol, new Queen('B', 'q'));
		else if (c == 'r')
			board.setPiece(dstRow, dstCol, new Rook('B', 'r'));
		else if (c == 'b')
			board.setPiece(dstRow, dstCol, new Bishop('B', 'b'));
		else if (c == 'n')
			board.setPiece(dstRow, dstCol, new Knight('B', 'n'));

	}

}

bool GameState::EnPassant(int srcRow, int srcCol, int dstRow, int dstCol)
{
	Piece* Ppiece = board.getPiece(srcRow, srcCol);

	if (Ppiece == nullptr)
		return false;


	if (!(Ppiece->getSymbol() == 'p' || Ppiece->getSymbol() == 'P'))
		return false;


	int rowDiff = dstRow - srcRow;
	int colDiff = dstCol - srcCol;

	int direction = (board.getPiece(srcRow, srcCol)->getColor() == 'W') ? -1 : 1;
	char color = board.getPiece(srcRow, srcCol)->getColor();

	if (board.getPiece(dstRow, dstCol) == nullptr)
	{
		if (rowDiff == direction && (colDiff == 1 || colDiff == -1))
		{
			if ((color == 'W' && srcRow == 3) || (color == 'B' && srcRow == 4))
			{
				if ((prevPiece == 'P' && currentTurn == 'B') || (prevPiece == 'p' && currentTurn == 'W'))
				{
					if ((prevDstRow - prevSrcRow == 2 || prevDstRow - prevSrcRow == -2) && (prevSrcCol == prevDstCol))
					{
						if ((prevDstCol == srcCol + 1 || prevDstCol == srcCol - 1) && prevDstRow == srcRow)
						{
							Piece* enemyPawn = board.getPiece(prevDstRow, prevDstCol);

							if (enemyPawn == nullptr)
								return false;

							if (enemyPawn->getColor() == color)
								return false;
							
							return true;

						}
					}
				}
			}

		}
	}

	return false;
}



bool GameState::Castling(int srcRow, int srcCol, int dstRow, int dstCol)
{
	Piece* Ppiece = board.getPiece(srcRow, srcCol);

	if (Ppiece == nullptr)
		return false;


	if (!(board.getPiece(srcRow, srcCol)->getSymbol() == 'K' || board.getPiece(srcRow, srcCol)->getSymbol() == 'k'))
		return false;

	

	//for white
	if (board.getPiece(srcRow, srcCol)->getColor() == 'W')
	{
		if (isInCheck('W', board))
			return false;
		//King Side Castling 
		if (whiteKingMoved == false && whiteRookHMoved == false)
		{
			if (srcRow == 7 && srcCol == 4)
			{
				if (board.getPiece(7, 4)->getSymbol() == 'K')
				{
					if (board.getPiece(7, 5) == nullptr && board.getPiece(7, 6) == nullptr && board.getPiece(7, 7) != nullptr && board.getPiece(7,7)->getSymbol() == 'R')
					{
						if (dstRow == 7 && dstCol == 6)
						{
							Board temp(board);
							temp.movePiece(7, 4, 7, 5);
							if (isInCheck('W', temp)) return false;

							
							temp.movePiece(7, 5, 7, 6);
							if (isInCheck('W', temp)) return false;
							return true;
						}
					}
				}

			}
			
		}

		//Queen Side castling
		if (whiteKingMoved == false && whiteRookAMoved == false)
		{
			if (srcRow == 7 && srcCol == 4)
			{
				if (board.getPiece(7, 4)->getSymbol() == 'K')
				{
					if (board.getPiece(7, 1) == nullptr && board.getPiece(7, 2) == nullptr && board.getPiece(7, 3) == nullptr && board.getPiece(7, 0) != nullptr && board.getPiece(7, 0)->getSymbol() == 'R')
					{
						if (dstRow == 7 && dstCol == 2)
						{
							Board temp(board);
							temp.movePiece(7, 4, 7, 3);
							if (isInCheck('W', temp)) return false;

							
							temp.movePiece(7, 3, 7, 2);
							if (isInCheck('W', temp)) return false;
							return true;
						}
					}
				}

			}
		}
	}

	//for niggas


	
	if (board.getPiece(srcRow, srcCol)->getColor() == 'B')
	{
		if (isInCheck('B', board))
			return false;
		//kingside
		if (blackKingMoved == false && blackRookHMoved == false)
		{
			if (srcRow == 0 && srcCol == 4)
			{
				if (board.getPiece(srcRow, srcCol)->getSymbol() == 'k')
				{
					if (board.getPiece(0, 5) == nullptr && board.getPiece(0, 6) == nullptr && board.getPiece(0, 7) != nullptr && board.getPiece(0, 7)->getSymbol() == 'r')
					{
						if (dstRow == 0 && dstCol == 6)
						{
							Board temp(board);
							temp.movePiece(0, 4, 0, 5);
							if (isInCheck('B', temp)) return false;

							temp.movePiece(0, 5, 0, 6);
							if (isInCheck('B', temp)) return false;
							return true;
						}
					}

				}
			}
		}

		//queenside
		if (blackKingMoved == false && blackRookAMoved == false)
		{
			if (srcRow == 0 && srcCol == 4)
			{
				if (board.getPiece(srcRow, srcCol)->getSymbol() == 'k')
				{
					if (board.getPiece(0, 1) == nullptr && board.getPiece(0, 2) == nullptr && board.getPiece(0, 3) == nullptr && board.getPiece(0, 0) != nullptr && board.getPiece(0, 0)->getSymbol() == 'r')
					{
						if (dstRow == 0 && dstCol == 2)
						{
							Board temp(board);
							temp.movePiece(0, 4, 0, 3);
							if (isInCheck('B', temp)) return false;

							temp.movePiece(0, 3, 0, 2);
							if (isInCheck('B', temp)) return false;

							return true;
						}
					}

				}
			}
		}
		
	}


	return false;
}


bool GameState::isInCheck(char color , Board& tempboard)
{
	int kingRow = -1;
	int kingCol = -1;
	char oppColor;
	//Opponent's Color
	if (color == 'W')
		 oppColor = 'B';
	else
		 oppColor = 'W';

	bool isFound = false;
	// Find the location of Player's King
	for (int i = 0; i < 8 && isFound == false; i++)
	{
		for (int j = 0; j < 8 && isFound == false; j++)
		{
			if (color == 'W')
			{
				if (tempboard.getPiece(i, j) != nullptr)
				{
					if (tempboard.getPiece(i, j)->getSymbol() == 'K')
					{
						kingRow = i;
						kingCol = j;
						isFound = true;
					}
				}
				
			}

			if (color == 'B')
			{
				if (tempboard.getPiece(i, j) != nullptr)
				{

				
					if (tempboard.getPiece(i, j)->getSymbol() == 'k')
					{
						kingRow = i;
						kingCol = j;
						isFound = true;
				
					}
				}
			}
		}
	}

	if (kingCol == -1 || kingRow == -1)
		return false;
	// King found
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* oppPiece = tempboard.getPiece(i, j);
			if (oppPiece != nullptr && oppPiece->getColor() == oppColor)
			{
				if (oppPiece->isValidMove(i, j, kingRow, kingCol, tempboard))
					return true;
			}
		}
	}


	return false;
}


bool GameState::isCheckmate(char color ,Board& board)
{
	if (isInCheck(color, board))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Piece* piece = board.getPiece(i, j);
				if (piece == nullptr || piece->getColor() != color)   //will move forward if only Piece only belongs to the player
					continue;


				for (int di = 0; di < 8; di++)
				{
					for (int dc = 0; dc < 8; dc++)
					{
						MoveValidator Valid;
						if ( Valid.IsValid( color, i ,j, di, dc, board ,false) == false)
						{
							continue;
						}

						Board temp = board; // must be a proper copy

						temp.movePiece(i, j, di, dc);

						if (isInCheck(color, temp) == false)
							return false;


					}
				}
			}
		}

		return true;
	
	}


	return false;


}


bool GameState::isStalemate(char color, Board& board)
{
	if (!(isInCheck(color, board)))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Piece* piece = board.getPiece(i, j);
				if (piece == nullptr || piece->getColor() != color)   //will move forward if only Piece only belongs to the player
					continue;


				for (int di = 0; di < 8; di++)
				{
					for (int dc = 0; dc < 8; dc++)
					{
						MoveValidator Valid;
						if (Valid.IsValid(color, i, j, di, dc, board, false) == false)
						{
							continue;
						}

						Board temp = board; // must be a proper copy

						temp.movePiece(i, j, di, dc);

						if (isInCheck(color, temp) == false)
							return false;


					}
				}
			}
		}

		return true;

	}


	return false;


}