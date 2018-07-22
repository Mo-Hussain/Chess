#include "Rook.h"

Rook::Rook(Colour colour, const char* symbol, ChessBoard* chessBoard):
           ChessPiece::ChessPiece(colour, symbol, "Rook", chessBoard){

}

bool Rook::validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                          ChessPosition* obstructions[]){

  if(ChessPosition::isLinearRankMove(start, end, steps, obstructions)){
      return true;
  }

  if(ChessPosition::isLinearFileMove(start, end, steps, obstructions)){
      return true;
  }
  return false;
}

