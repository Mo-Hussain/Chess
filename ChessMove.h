/**
 * class used to represent a chess move
 * contains a pointer to a ChessPiece, ChessPosition (start position of move),
 * an array pointers to ChessPositions on the path of the move and the number of
 * steps in the move
 */

#ifndef CHESSMOVE
#define CHESSMOVE

#include "ChessPiece.h"
#include "ChessPosition.h"

#define MAX_PATH 6

class ChessMove{
private:
	ChessPiece* piece;
	ChessPosition* piecePosition;
	ChessPosition* path[MAX_PATH];
	int steps;
public:
	ChessMove(ChessPiece* piece, ChessPosition* piecePosition, int steps, ChessPosition* path[]);
	//returns ChessPiece pointer
	ChessPiece* getPiece();
	// return ChessPosition pointer
	ChessPosition* getPiecePosition();
	// returns a pointer to an array of ChessPosition of the path
	ChessPosition** getPath();
	// returns a pointer to a positions a numbered step on the path
	ChessPosition* getPathPosition(int posNum);
	// returns the number of steps in the move 
	int getSteps();

};

#endif
