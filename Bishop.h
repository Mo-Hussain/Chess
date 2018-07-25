#ifndef BISHOP
#define BISHOP

#include "ChessMove.h"

class Bishop:public ChessPiece
{
public:
  Bishop(Colour colour, const char* symbol, ChessBoard* chessBoard);
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps, ChessPosition* obstructions[]);
};

#endif
