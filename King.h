#ifndef KING
#define KING

#include "ChessPiece.h"

class King:public ChessPiece{

public:
  King(Colour colour, const char* symbol, ChessBoard* chessBoard);
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]);

};

#endif
