#ifndef ROOK
#define ROOK

#include "ChessPiece.h"

class Rook:public ChessPiece{
	
public:
  Rook(Colour colour, const char* symbol, ChessBoard* chessBoard);
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]);

};

#endif
