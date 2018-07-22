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
