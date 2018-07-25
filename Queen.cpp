#include "Queen.h"

Queen::Queen(Colour colour, const char* symbol, ChessBoard* chessBoard):
             ChessPiece::ChessPiece(colour, symbol, "Queen", chessBoard){

}

bool Queen::validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                          ChessPosition* obstructions[]){

  if(ChessMove::isLinearRankMove(start, end, steps, obstructions)){
      return true;
  }

  if(ChessMove::isLinearFileMove(start, end, steps, obstructions)){
      return true;
  }

  if(ChessMove::isDiagonalMove(start, end, steps, obstructions)){
      return true;
  }
  return false;
}
