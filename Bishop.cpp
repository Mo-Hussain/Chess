#include "Bishop.h"

Bishop::Bishop(Colour colour, const char* symbol, ChessBoard* chessBoard):
              ChessPiece::ChessPiece(colour, symbol, "Bishop", chessBoard){

}

bool Bishop::validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                          ChessPosition* obstructions[]){

  if(ChessPosition::isDiagonalMove(start, end, steps, obstructions)){
      return true;
  }
  return false;
}

