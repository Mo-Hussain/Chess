#ifndef  CHESSEXCEPTION
#define CHESSEXCEPTION

#include <exception>
#include <cstdio>
#include <iostream>

using namespace std;

class chessException: public exception{
protected:
  char output[256];
public:
   const char * what() const throw(){
     return output;
   }
};

class invalidSourceSquare: public chessException{
private:
  const char* startPos;
public:
  invalidSourceSquare(const char* _startPos):startPos(_startPos){
    sprintf(output, "There is no piece at position %s!", startPos);
  }
};

class invalidPiece: public chessException{
private:
  const char* colour;
public:
  invalidPiece(const char* _colour):colour(_colour){
    sprintf(output, "It is not %s’s turn to move!", colour);
  }
};

class invalidEndPiece: public chessException{
private:
  const char* name;
  const char* colour;
  const char* startPos;
public:
  invalidEndPiece(const char* _name, const char* _colour, const char* _startPos):
                  name(_name), colour(_colour), startPos(_startPos){
    sprintf(output, "%s's %s cannot move to %s!", colour, name, startPos);
  }
};

#endif
