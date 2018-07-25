#ifndef QUEEN
#define QUEEN

#include "ChessMove.h"


class Queen:public ChessPiece{

public:
  Queen(Colour colour, const char* symbol, ChessBoard* chessBoard);
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]);

};

#endif
