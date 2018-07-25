#include "ChessMove.h"

ChessMove::ChessMove(ChessPiece* _piece, ChessPosition* _piecePosition, int _steps,  ChessPosition* _path[]):
					 piece(_piece), piecePosition(_piecePosition), steps(_steps){

	for(int i = 0; i < steps-1; i++){
		path[i] = _path[i];
	}
}
ChessPiece* ChessMove::getPiece(){
	return piece;
}
ChessPosition* ChessMove::getPiecePosition(){
	return piecePosition;
}
ChessPosition* ChessMove::getPathPosition(int posNum){
	return path[posNum];
}
int ChessMove::getSteps(){
	return steps;
}
ChessPosition** ChessMove::getPath(){
	return path;
}

bool ChessMove::isLinearRankMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]){
  if(start.getFile() != end.getFile()){;
    return false;
  }
  steps = abs(end.getRank() - start.getRank());

  for(int i = 0; i < steps-1; i++){
    if(start.getRank() < end.getRank()){
      obstructions[i] = new ChessPosition(start.getRank() + i+1, start.getFile());
    }
    if(start.getRank() > end.getRank()){
      obstructions[i] = new ChessPosition(start.getRank() - i-1, start.getFile());
    }
  }
  return true;
}

bool ChessMove::isLinearFileMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]){
  if(start.getRank() != end.getRank()){
    return false;
  }
  steps = abs(end.getFile() - start.getFile());

  for(int i = 0; i < steps-1; i++){
    if(start.getFile() < end.getFile()){
      obstructions[i] = new ChessPosition(start.getRank(), start.getFile() + i+1);
    }
    if(start.getFile() > end.getFile()){
      obstructions[i] = new ChessPosition(start.getRank(), start.getFile() - i-1);
    }
  }
  return true;
}

bool ChessMove::isDiagonalMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]){
  int changeInFile = abs(end.getFile() - start.getFile());
  int changeInRank = abs(end.getRank() - start.getRank());

  if (changeInFile != changeInRank){
    return false;
  }
  steps = changeInFile;

  for(int i = 0; i < steps-1; i++){
    if(start.getRank() < end.getRank()){
      if(start.getFile() < end.getFile()){
        obstructions[i] = new ChessPosition(start.getRank() + i+1, start.getFile() + i+1);
      }
      if(start.getFile() > end.getFile()){
        obstructions[i] = new ChessPosition(start.getRank() + i+1, start.getFile() - i-1);
      }
    }
    if(start.getRank() > end.getRank()){
      if(start.getFile() < end.getFile()){
        obstructions[i] = new ChessPosition(start.getRank() - i-1, start.getFile() + i+1);
      }
      if(start.getFile() > end.getFile()){
        obstructions[i] = new ChessPosition(start.getRank() - i-1, start.getFile() - i-1);
      }
    }
  }
  return true;
}

bool ChessMove::isKnightMove(ChessPosition start, ChessPosition end, int& steps){
  int changeInFile = abs(end.getFile() - start.getFile());
  int changeInRank = abs(end.getRank() - start.getRank());
  steps = 1;
  if(changeInFile == 1 && changeInRank == 2){
    return true;
  }
  if(changeInFile == 2 && changeInRank == 1){
    return true;
  }
  return false;
}
