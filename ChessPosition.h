#ifndef CHESSPOSITION
#define CHESSPOSITION

#include <stdlib.h>
#include <iostream>

#define ASCI_CHAR_CONVERSION 65
#define ASCI_INT_CONVERSION 49
using namespace std;

class ChessPosition{
private:
  int rank;
  int file;
public:
  ChessPosition(int rank, int file);
  int getRank();
  int getFile();
  void setRank(int _rank);
  void setFile(int _file);
  bool static isLinearRankMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]);
  bool static isLinearFileMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]);
  bool static isDiagonalMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]);
  bool static isKnightMove(ChessPosition start, ChessPosition end, int& steps);
  void getNieghbors(ChessPosition* nieghbors[]);
  bool nextPosition();
  void printPos(const char* pieceName);
  bool operator ==(const ChessPosition rhs);
  bool isPosinPath(ChessPosition* path[], int pathNum);

};

#endif
