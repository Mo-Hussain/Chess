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
	ChessPiece* getPiece();
	ChessPosition* getPiecePosition();
	ChessPosition** getPath();
	ChessPosition* getPathPosition(int posNum);
	int getSteps();

};

#endif
