#include "Pawn.h"

Pawn::Pawn(Colour colour, const char* symbol, ChessBoard* chessBoard):
      ChessPiece::ChessPiece(colour, symbol, "Pawn", chessBoard){
  hasMoved = false;
}

bool Pawn::validateMove(ChessPosition start, ChessPosition end, ChessPiece* endPiece, int& steps,
                          ChessPosition* obstructions[]){
  // checks for reversal
  if(colour == black){
    if(end.getRank() > start.getRank()){
      return false;
    }
  }
  else{
    if(end.getRank() < start.getRank()){
      return false;
    }
  }

  if(ChessPosition::isLinearRankMove(start, end, steps, obstructions) && steps == 1){
    if(endPiece == nullptr){
      hasMoved = true;
      return true;
    }
    return false;
  }

  if(ChessPosition::isLinearRankMove(start, end, steps, obstructions) && (steps == 2) && !hasMoved){
    if(endPiece == nullptr){
      hasMoved = true;
      return true;
    }
    return false;
  }

  if(ChessPosition::isDiagonalMove(start, end, steps, obstructions) && steps == 1){
    if(endPiece == nullptr){
      return false;
    }
    return true;
  }
}

