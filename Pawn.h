#ifndef PAWN
#define PAWN

#include "ChessMove.h"


class Pawn:public ChessPiece{
private:
  bool hasMoved;

public:
  Pawn(Colour colour, const char* symbol, ChessBoard* chessBoard);
  bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]);

};

#endif
