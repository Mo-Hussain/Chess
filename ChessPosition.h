/**
 * class used to represent a chess baord position
 * contains a rank and file integer values
 */


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
  // get an array of positions that neighbor the current position
  void getNieghbors(ChessPosition* nieghbors[]);
  // used to loop through all available positions on a baord
  bool nextPosition();
  // printing for debugg
  void printPos(const char* pieceName);
  // check if two positions are equal
  bool operator ==(const ChessPosition rhs);
  // check if the position is in a path of positions 
  bool isPosinPath(ChessPosition* path[], int pathNum);

};

#endif
