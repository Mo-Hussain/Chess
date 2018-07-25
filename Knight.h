#ifndef KNIGHT
#define KNIGHT

#include "ChessMove.h"

class Knight:public ChessPiece{

public:
  Knight(Colour colour,  const char* symbol, ChessBoard* chessBoard);
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]);

};

#endif
