#include "ChessPiece.h"

ChessPiece::ChessPiece(Colour _colour, const char* _symbol, const char* _name,  ChessBoard* _chessBoard):
											colour(_colour), symbol(_symbol), name(_name), chessBoard(_chessBoard)
{
}

Colour ChessPiece::getColour(){
	return colour;
}

const char* ChessPiece::getName(){
	return name;
}
