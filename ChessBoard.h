#ifndef CHESSBOARD
#define CHESSBOARD

#include <iostream>
#include <cstring>
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "ChessMove.h"

#define GRID_WIDTH 8
#define GRID_HEIGHT 8
#define NUM_PER_PLAYER 16
#define NUM_OF_BLACK 16
#define TOTAL_NUM_PIECES 32
#define ASCI_CHAR_CONVERSION 65
#define ASCI_INT_CONVERSION 49
#define MAX_NUM_NEIGHBORS 8

using namespace std;

class ChessBoard{
private:
  ChessPiece* board[GRID_HEIGHT][GRID_WIDTH];
  ChessPosition* blackKing;
  ChessPosition* whiteKing;
  Colour currentTurn;

public:
  ChessBoard();
  void submitMove(const char* startPos, const char* endPos);
  void resetBoard();
  void setupBoard();
  void printChessBoard();
  void changeTurn();
  ChessPosition convertMove(const char* Pos);
  ChessPiece* getPiece(ChessPosition position);
  const char* getColourString(Colour colour);
  void movePiece(ChessPiece* selectedPiece, ChessPiece* endPiece,
                 ChessPosition start, ChessPosition end);
  void reverseMove(ChessPiece* strPiece, ChessPiece* endpiece, ChessPosition start, ChessPosition end);
  bool isMoveObstructed(int steps, ChessPosition* obstructions[]);
  bool isInCheck(ChessPosition* kingPos, ChessMove** threatMoves, ChessMove** obstructedThreatMoves, int& numThreatMoves, int& numObsMoves);
  bool testMove(ChessPiece* selectedPiece, ChessPosition strPos, ChessPiece* endPiece, ChessPosition ePos, ChessPosition* kingPos);
  bool isCheckMate(ChessPosition* kingPos, ChessMove** threatMoves, ChessMove** obstructedThreatMoves, int numThreatMoves, int numObsMoves);
  bool canPieceDefend(ChessMove* chessMove, ChessPiece* piece, ChessPosition* piecePos, ChessPosition* kingPos);
  void printMove(ChessPiece* piece, ChessPiece* endPiece, const char* startPos, const char* endPos);
  void printNiegbors(ChessPosition* nieghbors[]);
  Colour switchColour();
  bool isInStalemate(ChessPosition* kingPos, ChessMove** obstructedThreatMoves, int numObsMoves);
  bool isInStalemate(ChessPosition* kingPos);



};


#endif
