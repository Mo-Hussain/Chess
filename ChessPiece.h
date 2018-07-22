#ifndef CHESSPIECE
#define CHESSPIECE

#include <iostream>
#include "ChessPosition.h"

using namespace std;

// forward declare chessboard class
class ChessBoard;

// enum for colour of chess piece
enum Colour {black, white};

class ChessPiece{
protected:
  Colour colour;
  const char* name;
  ChessBoard* chessBoard;
public:
  const char* symbol;
  ChessPiece(Colour colour, const char* symbol, const char* name, ChessBoard* chessBoard);
  Colour getColour();
  const char* getName();
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]) = 0;
};

#endif
