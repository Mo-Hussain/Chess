#include "King.h"

King::King(Colour colour, const char* symbol, ChessBoard* chessBoard):
           ChessPiece::ChessPiece(colour, symbol, "King", chessBoard){

}

bool King::validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                          ChessPosition* obstructions[]){

  if(ChessMove::isLinearRankMove(start, end, steps, obstructions) && steps == 1 ){
      return true;
  }

  if(ChessMove::isLinearFileMove(start, end, steps, obstructions) && steps == 1){
      return true;
  }

  if(ChessMove::isDiagonalMove(start, end, steps, obstructions) && steps == 1){
      return true;
  }
  return false;
}
