#include "Knight.h"

Knight::Knight(Colour colour, const char* symbol, ChessBoard* chessBoard):
               ChessPiece::ChessPiece(colour, symbol, "Knight", chessBoard){

}

bool Knight::validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                          ChessPosition* obstructions[]){
  if(ChessPosition::isKnightMove(start, end, steps)){
      return true;
  }
  return false;
}

