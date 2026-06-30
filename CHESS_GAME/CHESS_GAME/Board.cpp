#include<iostream>
#include"Board.h"
#include"Piece.h"
#include"Rook.h"
#include"Bishop.h"
#include"King.h"
#include"Knight.h"
#include"Pawn.h"
#include"Queen.h"
#include <windows.h>



using namespace std;

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			grid[i][j] = nullptr;
	}
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete grid[i][j];
			grid[i][j] = nullptr;
		}
	}
}

//Copy Constructor

Board::Board(const Board& board)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			grid[i][j] = nullptr;

			Piece* p = board.grid[i][j];

			if (p == nullptr)
				continue;

			switch (p->getSymbol())
			{
			case 'P':
				grid[i][j] = new Pawn('W', 'P');
				break;

			case 'p':
				grid[i][j] = new Pawn('B', 'p');
				break;

			case 'R':
				grid[i][j] = new Rook('W', 'R');
				break;

			case 'r':
				grid[i][j] = new Rook('B', 'r');
				break;

			case 'N':
				grid[i][j] = new Knight('W', 'N');
				break;

			case 'n':
				grid[i][j] = new Knight('B', 'n');
				break;

			case 'B':
				grid[i][j] = new Bishop('W', 'B');
				break;

			case 'b':
				grid[i][j] = new Bishop('B', 'b');
				break;

			case 'Q':
				grid[i][j] = new Queen('W', 'Q');
				break;

			case 'q':
				grid[i][j] = new Queen('B', 'q');
				break;

			case 'K':
				grid[i][j] = new King('W', 'K');
				break;

			case 'k':
				grid[i][j] = new King('B', 'k');
				break;
			}
		}
	}
}



void Board::print()
{
	setColor(15);
	cout << "    a    b    c    d    e    f    g    h" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout <<" "<<(8 - i);
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] == nullptr)
			{
				setColor(15);
				cout << " [ ] ";

			}
			else
			{
				if (grid[i][j]->getColor() == 'W')
				{
					setColor(13);
					cout << " [" << grid[i][j]->getSymbol() << "] ";

				}

				if (grid[i][j]->getColor() == 'B')
				{
					setColor(11);
					cout << " [" << grid[i][j]->getSymbol() << "] ";

				}

			}
		}
		setColor(15);
		cout <<" "<< (8 - i) << endl;

	}
	cout << "    a    b    c    d    e    f    g    h" << endl;

}

void Board::initialize()
{
	//Thisss is for da Niggas
	grid[0][0] = new Rook('B','r');
	grid[0][1] = new Knight('B','n');
	grid[0][2] = new Bishop('B','b');
	grid[0][3] = new Queen('B','q');
	grid[0][4] = new King('B','k');
	grid[0][5] = new Bishop('B','b');
	grid[0][6] = new Knight('B','n');
	grid[0][7] = new Rook('B','r');
	//Nigga Pawns
	for (int i = 0; i < 8; i++)
	{
		grid[1][i] = new Pawn('B','p');
	}

	// Thiss for Anti Niggas
	grid[7][0] = new Rook('W','R');
	grid[7][1] = new Knight('W','N');
	grid[7][2] = new Bishop('W','B');
	grid[7][3] = new Queen('W','Q');
	grid[7][4] = new King('W','K');
	grid[7][5] = new Bishop('W','B');
	grid[7][6] = new Knight('W','N');
	grid[7][7] = new Rook('W','R');

	// Anti Nigga Pawns
	for (int i = 0; i < 8; i++)
	{
		grid[6][i] = new Pawn('W','P');
	}


}

bool Board::movePiece(int srcRow, int srcCol, int dstRow, int dstCol)
{
	if (grid[dstRow][dstCol] == nullptr)
	{
		grid[dstRow][dstCol] = grid[srcRow][srcCol];
		grid[srcRow][srcCol] = nullptr;
	}

	//Now there is a piece a destination

	else
	{
		delete grid[dstRow][dstCol];
		grid[dstRow][dstCol] = grid[srcRow][srcCol];
		grid[srcRow][srcCol] = nullptr;
	}
	
	return true;

}

Piece* Board::getPiece(int row, int col)
{
	return grid[row][col];
}


void Board::setPiece(int row, int col, Piece* piece)
{
	delete grid[row][col];
	grid[row][col] = piece;
}


void Board::setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


