#include "ChessPosition.h"

ChessPosition::ChessPosition(int _rank, int _file): rank(_rank), file(_file){

}

int ChessPosition::getRank(){
  return rank;
}

int ChessPosition::getFile(){
  return file;
}

bool ChessPosition::isLinearRankMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]){
  if(start.file != end.file){;
    return false;
  }
  steps = abs(end.rank - start.rank);

  for(int i = 0; i < steps-1; i++){
    if(start.rank < end.rank){
      obstructions[i] = new ChessPosition(start.rank + i+1, start.file);
    }
    if(start.rank > end.rank){
      obstructions[i] = new ChessPosition(start.rank - i-1, start.file);
    }
  }
  return true;
}

bool ChessPosition::isLinearFileMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]){
  if(start.rank != end.rank){
    return false;
  }
  steps = abs(end.file - start.file);

  for(int i = 0; i < steps-1; i++){
    if(start.file < end.file){
      obstructions[i] = new ChessPosition(start.rank, start.file + i+1);
    }
    if(start.file > end.file){
      obstructions[i] = new ChessPosition(start.rank, start.file - i-1);
    }
  }
  return true;
}

bool ChessPosition::isDiagonalMove(ChessPosition start, ChessPosition end, int& steps, ChessPosition* obstructions[]){
  int changeInFile = abs(end.file - start.file);
  int changeInRank = abs(end.rank - start.rank);

  if (changeInFile != changeInRank){
    return false;
  }
  steps = changeInFile;

  for(int i = 0; i < steps-1; i++){
    if(start.rank < end.rank){
      if(start.file < end.file){
        obstructions[i] = new ChessPosition(start.rank + i+1, start.file + i+1);
      }
      if(start.file > end.file){
        obstructions[i] = new ChessPosition(start.rank + i+1, start.file - i-1);
      }
    }
    if(start.rank > end.rank){
      if(start.file < end.file){
        obstructions[i] = new ChessPosition(start.rank - i-1, start.file + i+1);
      }
      if(start.file > end.file){
        obstructions[i] = new ChessPosition(start.rank - i-1, start.file - i-1);
      }
    }
  }
  return true;
}

bool ChessPosition::isKnightMove(ChessPosition start, ChessPosition end, int& steps){
  int changeInFile = abs(end.file - start.file);
  int changeInRank = abs(end.rank - start.rank);
  steps = 1;
  if(changeInFile == 1 && changeInRank == 2){
    return true;
  }
  if(changeInFile == 2 && changeInRank == 1){
    return true;
  }
  return false;
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
