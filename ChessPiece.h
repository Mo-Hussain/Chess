/**
 * class used to represent a chess piece
 * contains an enum to represent the colour of the piece, a name, a pointer to
 * the ChessBoard it is on and a symbol to represent it
 */

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
  // return colour of piece
  Colour getColour();
  // return name
  const char* getName();
  // vitual function to validate a move for this piece 
  virtual bool validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                            ChessPosition* obstructions[]) = 0;
};

#endif
