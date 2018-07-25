/**
 * class used to represent a chess board contains a 2 dimentional array of ChessPieces
 * pointers to ChessPositions of the black ans white kings, and the colour of the current turn
 *
 */

 /*
    board repesentations

    A8 B8 C8 D8 E8 F8 G8 H8
    A7 B7 C7 D7 E7 F7 G7 H7
    A6 B6 C6 D6 E6 F6 G6 H6
    A5 B5 C5 D5 E5 F5 G5 H5
    A4 B4 C4 D4 E4 F4 G4 H4
    A3 B3 C3 D3 E3 F3 G3 H3
    A2 B2 C2 D2 E2 F2 G2 H2
    A1 B1 C1 D1 E1 F1 G1 H1

 */


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
  // move submitted in the form "B7", see repesentation above
  void submitMove(const char* startPos, const char* endPos);
  // restart the board from the start position
  void resetBoard();
  // initiate board
  void setupBoard();
  // print board to console for debugging
  void printChessBoard();
  // switch the turn at the end of the move
  void changeTurn();
  // converts a position in the form of "B6" to ChessPosition object
  ChessPosition convertPosition(const char* Pos);
  // return piece at a ChessPostion on the board
  ChessPiece* getPiece(ChessPosition position);
  // return a string for a colour
  const char* getColourString(Colour colour);
  // move the selected piece from start to end positions
  void movePiece(ChessPiece* selectedPiece, ChessPosition start, ChessPosition end);
  // reverse a move
  void reverseMove(ChessPiece* strPiece, ChessPiece* endpiece, ChessPosition start, ChessPosition end);
  // check if a move is obstructed by another piece
  bool isMoveObstructed(int steps, ChessPosition* obstructions[]);
  // check if a king in in check using a array of threatening and obstructed threstening moves available to the oposition
  bool isInCheck(ChessPosition* kingPos, ChessMove** threatMoves, ChessMove** obstructedThreatMoves, int& numThreatMoves, int& numObsMoves);
  // test a move to see if it is valid, checking also if it is putting you in check
  bool testMove(ChessPiece* selectedPiece, ChessPosition strPos, ChessPiece* endPiece, ChessPosition ePos, ChessPosition* kingPos);
  // check if player is in checkmate
  bool isCheckMate(ChessPosition* kingPos, ChessMove** threatMoves, ChessMove** obstructedThreatMoves, int numThreatMoves, int numObsMoves);
  // check if a piece has a valid move to protect its king which is in check
  bool canPieceDefend(ChessMove* chessMove, ChessPiece* piece, ChessPosition* piecePos, ChessPosition* kingPos);
  // print move for debugging
  void printMove(ChessPiece* piece, ChessPiece* endPiece, const char* startPos, const char* endPos);
  // print neigbors of piece for debugging
  void printNiegbors(ChessPosition* nieghbors[]);
  Colour switchColour();
  // check if game is in stalemate 
  bool isInStalemate(ChessPosition* kingPos, ChessMove** obstructedThreatMoves, int numObsMoves);
  bool isInStalemate(ChessPosition* kingPos);



};


#endif
