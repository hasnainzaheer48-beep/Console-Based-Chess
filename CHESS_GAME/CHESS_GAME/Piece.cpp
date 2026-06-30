#include"Piece.h"
#include<iostream>

char Piece::getColor()
{
	return color;
}

char Piece::getSymbol()
{
	return symbol;
}

Piece::Piece(char color, char symbol)
{
	this->color = color;
	this->symbol = symbol;
}