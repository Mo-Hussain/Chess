#include "ChessPosition.h"

ChessPosition::ChessPosition(int _rank, int _file): rank(_rank), file(_file){
}

int ChessPosition::getRank(){
  return rank;
}

int ChessPosition::getFile(){
  return file;
}

void ChessPosition::setRank(int _rank){
  rank = _rank;
}

void ChessPosition::setFile(int _file){
  file = _file;
}

void ChessPosition::getNieghbors(ChessPosition* nieghbors[]){
  fill_n(nieghbors, 8, nullptr);
  int search[3] = {0,1,-1};
  int numOfNeighbors = 0;
  int newRank;
  int newFile;
  int loop = 0;

  for(int i = 0; i <= 2; i++){
    for(int j = 0; j <= 2; j++){
      if(i == 0 && j == 0)
      {
      }
      else{
        loop++;
        newRank = rank + search[i];
        newFile = file + search[j];
        if(newRank <= 7 && newRank >= 0 && newFile <= 7 && newFile >= 0){
          ChessPosition* pos = new ChessPosition(newRank, newFile);
          nieghbors[numOfNeighbors] = pos;
          numOfNeighbors++;
        }
      }
    }
  }
}

bool ChessPosition::nextPosition(){
  if(rank == 7 && file == 7){
    return false;
  }

  if(file == 7){
    rank++;
    file= 0;
    return true;
  }

  file++;
  return true;
}

void ChessPosition::printPos(const char* pieceName){
  cout << pieceName << " has position " << (char)(file+ASCI_CHAR_CONVERSION) << (char)(rank+ASCI_INT_CONVERSION) << endl;
}

bool ChessPosition::operator ==(const ChessPosition rhs){
  if(rank == rhs.rank && file == rhs.file){
    return true;
  }
  return false;
}

bool ChessPosition::isPosinPath(ChessPosition* path[], int pathNum){
  for(int i = 0; i < pathNum; i++){
    if(*path[i] == *this){
      return true;
    }
  }
  return false;
}
