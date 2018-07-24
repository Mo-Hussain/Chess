#include "ChessBoard.h"
#include "chessExceptions.h"

ChessBoard::ChessBoard(){
  setupBoard();
  currentTurn = white;
  blackKing = new ChessPosition(7,4);
  whiteKing = new ChessPosition(0,4);
}

// main method for handling a move
void ChessBoard::submitMove(const char* startPos, const char* endPos){
  ChessPosition* myKingPos;
  ChessPosition* opsKingPos;

  int steps;
  ChessPosition* obstructions[GRID_WIDTH];

  ChessMove* checkMoves[NUM_PER_PLAYER];
  ChessMove* obstructedCheckMoves[NUM_PER_PLAYER];

  int numObsMoves = 0;
  int numObsCheckMoves = 0;

  // convert move into ChessPosition object for start and end positions
  ChessPosition strPos = convertMove(startPos);
  ChessPosition ePos = convertMove(endPos);

  // retrieves pieces a thos positions
  ChessPiece* selectedPiece = getPiece(strPos);
  ChessPiece* endSquare = getPiece(ePos);

  // set local king ChessPosition pointers
  if(currentTurn == black){
    myKingPos = blackKing;
    opsKingPos = whiteKing;
  }
  else{
    myKingPos = whiteKing;
    opsKingPos = blackKing;
  }


  try
  {
    // check to see if there is a piece at the starting square
    if(selectedPiece == nullptr){
      invalidSourceSquare error(startPos);
      throw(error);
    }

    // check to see if it is the turn of the selected piece
    if(selectedPiece->getColour() != currentTurn){
      invalidPiece error (getColourString(selectedPiece->getColour()));
      throw(error);
    }

    // check to see if end square piece is the same colour as selected piece
    if(endSquare != nullptr && endSquare->getColour() == currentTurn){
      invalidEndPiece error(selectedPiece->getName(),
                            getColourString(selectedPiece->getColour()), endPos);
      throw(error);
    }
    // check if piece can make the move and return the number ob steps and and array of chesspositions in its path
    if(!selectedPiece->validateMove(strPos, ePos, endSquare, steps, obstructions)){
      invalidEndPiece error(selectedPiece->getName(),
                            getColourString(selectedPiece->getColour()), endPos);
      throw(error);
    }
    // check if the path is obstructed
    if(steps > 1 && isMoveObstructed(steps, obstructions)){
      invalidEndPiece error(selectedPiece->getName(),
                            getColourString(selectedPiece->getColour()), endPos);
      throw(error);
    }
    // make the move, see if this puts current king in check, if so reverse the move (maybe wierd behavior if the current piece is the king)
    if(!testMove(selectedPiece, strPos, endSquare, ePos, myKingPos)){
      invalidEndPiece error(selectedPiece->getName(),
                            getColourString(selectedPiece->getColour()), endPos);
      throw(error);
    }

    // move the piece
    movePiece(selectedPiece, endSquare, strPos, ePos);

    // if the current piece is king adjust the king pointer
    if(strcmp(selectedPiece->getName(),"King") == 0){
      if(currentTurn == black){
        *blackKing = ePos;
        myKingPos = blackKing;
      }
      else{
        *whiteKing = ePos;
        myKingPos = whiteKing;

      }
    }

    // print move
    printMove(selectedPiece, endSquare, startPos, endPos);

    // check for check on opposition king
    if(isInCheck(opsKingPos, checkMoves, obstructedCheckMoves, numObsMoves, numObsCheckMoves)){
      // check for checkmate
      if(isCheckMate(opsKingPos, checkMoves, obstructedCheckMoves, numObsMoves, numObsCheckMoves)){
        cout << getColourString(switchColour()) << " is in checkmate" << endl;
      }
      else{
        cout << getColourString(switchColour()) << " is in check" << endl;
      }
    }
  }
  catch (exception& e)
  {
    cerr << e.what() << endl;
  }

  // change turn
  changeTurn();
}

// reset the board
void ChessBoard::resetBoard(){
  setupBoard();
  currentTurn = white;
  blackKing = new ChessPosition(7,4);
  whiteKing = new ChessPosition(0,4);
}

// print chessboard for debugging
void ChessBoard::printChessBoard(){
  cout << endl;
  cout << " ";
  for(int j = 0; j <= 7; j++){
    cout << (char)(j+ASCI_CHAR_CONVERSION) << "   ";
  }
  cout << endl;

  for(int i = 7; i >= 0; i--){
    for(int j = 0; j <= 7; j++){
      cout << "|";
      if (board[i][j] != nullptr){
           cout << board[i][j]->symbol;
      }
      else{
        cout << "  ";
      }
      cout << "|";

    }
    cout << " " << i+1 << endl;
  }
  cout << endl;
}

// convert the input move to a array positions for source and end
ChessPosition ChessBoard::convertMove(const char* position){
    int rank  = (int)position[1] - ASCI_INT_CONVERSION;
    int file = (int)position[0] - ASCI_CHAR_CONVERSION;
    ChessPosition chessPosition(rank, file);
    return chessPosition;
}

// create chess pieces on heap and place them on the board
void ChessBoard::setupBoard(){
  cout << "A new chess game is started!" << endl;

  board[0][0] = new Rook(white, "rw", this);
  board[0][1] = new Knight(white, "hw", this);
  board[0][2] = new Bishop(white, "bw", this);
  board[0][3] = new Queen(white, "qw", this);
  board[0][4] = new King(white, "kw", this);
  board[0][7] = new Rook(white, "rw", this);
  board[0][6] = new Knight(white, "hw", this);
  board[0][5] = new Bishop(white, "bw", this);

  board[7][0] = new Rook(black, "rb", this);
  board[7][1] = new Knight(black, "hb", this);
  board[7][2] = new Bishop(black, "bb", this);
  board[7][3] = new Queen(black, "qb", this);
  board[7][4] = new King(black, "kb", this);
  board[7][7] = new Rook(black, "rb", this);
  board[7][6] = new Knight(black, "hb", this);
  board[7][5] = new Bishop(black, "bb", this);

  for(int i = 0; i <= 7; i++){
    board[1][i] = new Pawn(white, "pw", this);
    board[6][i] = new Pawn(black, "pb", this);
  }

  for(int i = 0; i <= 7; i++){
    for(int j = 2; j <= 5; j++){
      board[j][i] = nullptr;
    }
  }
}

// change the current player turn
void ChessBoard::changeTurn(){
  if(currentTurn == white){
    currentTurn = black;
    return;
  }
  currentTurn = white;
}

// return string
const char* ChessBoard::getColourString(Colour colour){
  switch(colour){
    case black: return "Black";
    case white: return "White";
  }
}

ChessPiece* ChessBoard::getPiece(ChessPosition position){
  return board[position.getRank()][position.getFile()];
}

void ChessBoard::movePiece(ChessPiece* selectedPiece, ChessPiece* endPiece, ChessPosition start, ChessPosition end){
  board[end.getRank()][end.getFile()] = selectedPiece;
  board[start.getRank()][start.getFile()] = nullptr;
}

void ChessBoard::reverseMove(ChessPiece* strPiece, ChessPiece* endpiece, ChessPosition start, ChessPosition end){
  board[start.getRank()][start.getFile()] = strPiece;
  board[end.getRank()][end.getFile()] = endpiece;
}

bool ChessBoard::isMoveObstructed(int steps, ChessPosition* obstructions[]){
  for(int i = 0; i < steps-1; i++){
    if(getPiece(*obstructions[i]) != nullptr){
      return true;
    }
  }
  return false;
}

bool ChessBoard::isInCheck(ChessPosition* kingPos, ChessMove** threatMoves, ChessMove** obstructedThreatMoves, int& numThreatMoves, int& numObsMoves){
  ChessPosition* pos = new ChessPosition(0,0);
  ChessPiece* piece;
  ChessMove* moves[NUM_PER_PLAYER];
  int numOfThreats = 0;

  ChessPiece* kingPiece = getPiece(*kingPos);
  Colour kingColour = kingPiece->getColour();

  // loop through board and get piece
  while(pos->nextPosition()){
      piece = getPiece(*pos);
      // check is piece is opposition
      if(piece != nullptr && piece->getColour() != kingColour){
        int steps;
        ChessPosition* obstructions[GRID_WIDTH];
        // check if opposition piece has valid move to king
        if(piece->validateMove(*pos, *kingPos, kingPiece, steps, obstructions)){
          // pos->printPos(piece->getName());

          // create ChessMove object
          ChessMove* move = new ChessMove(piece, pos, steps, obstructions);
          // add move to moves array
          moves[numOfThreats] = move;
          numOfThreats++;
        }
      }
    }


  if(numOfThreats > 0){
    for(int i = 0; i < numOfThreats; i++){
      if(isMoveObstructed(moves[i]->getSteps(), moves[i]->getPath())){
         obstructedThreatMoves[numThreatMoves] = moves[i];
         numThreatMoves++;
      }
      else{
        threatMoves[numObsMoves] = moves[i];
        numObsMoves++;
      }
    }
  }

  if(numObsMoves > 0){
    return true;
  }
  return false;
}

bool ChessBoard::testMove(ChessPiece* selectedPiece, ChessPosition strPos, ChessPiece* endPiece, ChessPosition ePos, ChessPosition* kingPos){
  // if start and end is equal return false
  if(strPos == ePos){
    return false;
  }

  movePiece(selectedPiece, endPiece, strPos, ePos);

  ChessMove* checkMoves[NUM_PER_PLAYER];
  ChessMove* obstructedCheckMoves[NUM_PER_PLAYER];
  int numThreatMoves = 0;
  int numObsCheckMoves= 0;

  if(strcmp(selectedPiece->getName(),"King") == 0){
    *kingPos = ePos;
  }

  if(isInCheck(kingPos, checkMoves, obstructedCheckMoves, numThreatMoves, numObsCheckMoves)){
    if(strcmp(selectedPiece->getName(),"King") == 0){
      *kingPos = strPos;
    }
    reverseMove(selectedPiece, endPiece, strPos, ePos);

    return false;
  }

  if(strcmp(selectedPiece->getName(),"King") == 0){
    *kingPos = strPos;
  }
  reverseMove(selectedPiece, endPiece, strPos, ePos);

  return true;
}

bool ChessBoard::isCheckMate(ChessPosition* kingPos, ChessMove** threatMoves, ChessMove** obstructedThreatMoves, int numThreatMoves, int numObsMoves){
  ChessPosition* neigbors[MAX_NUM_NEIGHBORS];
  kingPos->getNieghbors(neigbors);
  ChessPiece* king = getPiece(*kingPos);
  Colour kingColour = king->getColour();

  // check if king can move to its nieghbors and avoid check
  for(int i = 0; i < 8; i++){
    if(neigbors[i] != nullptr){
      // cout << i << " ";
      // neigbors[i]->printPos("neigbor");
      if(getPiece(*neigbors[i]) != nullptr){
        if((getPiece(*neigbors[i])->getColour() != kingColour) && testMove(king, *kingPos, getPiece(*neigbors[i]), *neigbors[i], kingPos)){
          // cout << "Leaving check mate as false due to king having valid move to nieghbor ";
          // neigbors[i]->printPos("that");
          // cout << "niegbour currently occupied by " << getColourString(getPiece(*neigbors[i])->getColour()) << " " << getPiece(*neigbors[i])->getName() << endl;
          return false;
        }
      }
      else if(testMove(king, *kingPos, getPiece(*neigbors[i]), *neigbors[i], kingPos)){
        // cout << "Leaving check mate as false due to king having valid move to nieghbor ";
        // neigbors[i]->printPos("that");
        // cout << "Which is currently unoccupied" << endl;
        return false;
      }
    }
  }

  if(numThreatMoves >= 2){
    return true;
  }

  ChessPosition* pos = new ChessPosition(0,0);
  ChessPiece* piece;
  ChessMove* move = threatMoves[0];

  while(pos->nextPosition()){
      piece = getPiece(*pos);
      // check if piece is same colour
      if(piece != nullptr && piece->getColour() == kingColour){
        if(canPieceDefend(move, piece, pos, kingPos)){
          return false;
        }
      }
  }

  return true;
}

bool ChessBoard::canPieceDefend(ChessMove* chessMove, ChessPiece* piece, ChessPosition* piecePos, ChessPosition* kingPos){
  int steps = 0;
  ChessPosition* obstructions[8];

  // test move which captures the threatening piece
  if(piece->validateMove(*piecePos, *(chessMove->getPiecePosition()), chessMove->getPiece(), steps, obstructions)){
    if(steps > 1 && !isMoveObstructed(steps, obstructions)){
      if(testMove(piece, *piecePos, chessMove->getPiece(), *(chessMove->getPiecePosition()), kingPos)){
        return true;
      }
    }
  }

  for(int i = 0; i < chessMove->getSteps()-1; i++){
    if(!piece->validateMove(*piecePos, *(chessMove->getPathPosition(i)), getPiece(*(chessMove->getPathPosition(i))), steps, obstructions)){
      return false;
    }

    if(steps > 1 && isMoveObstructed(steps, obstructions)){
      return false;
    }

    if(!testMove(piece, *piecePos, getPiece(*(chessMove->getPathPosition(i))), *(chessMove->getPathPosition(i)), kingPos)){
      return false;
    }
    return true;
  }
}

void ChessBoard::printMove(ChessPiece* selectedPiece, ChessPiece* endPiece, const char* startPos, const char* endPos){
  if(endPiece != nullptr){
    cout << getColourString(selectedPiece->getColour()) << "'s " << selectedPiece->getName() << " moves from " << startPos << " to " << endPos <<
    " taking " << getColourString(endPiece->getColour()) << "'s " << endPiece->getName() << endl;
  }
  else{
    cout << getColourString(selectedPiece->getColour()) << "'s " << selectedPiece->getName() << " moves from " << startPos << " to " << endPos << endl;
  }
}

void ChessBoard::printNiegbors(ChessPosition* nieghbors[]){
  for(int i = 0; i < MAX_NUM_NEIGHBORS; i++){
    if(nieghbors[i] != nullptr){
      if(getPiece(*nieghbors[i]) != nullptr){
        cout << i << " ";
        cout << getColourString(getPiece(*nieghbors[i])->getColour()) << " " << getPiece(*nieghbors[i])->getName();
        nieghbors[i]->printPos("");
      }
      else{
        cout << i << " ";
        nieghbors[i]->printPos("niegbour is chess piece nullptr which");
      }
    }
    else{
      cout << "nieghbor " << i << " is nullptr" << endl;
    }
  }
}

Colour ChessBoard::switchColour(){
  if(currentTurn == black){
    return white;
  }
  else{
    return black;
  }
}

bool ChessBoard::isInStalemate(ChessPosition* kingPos, ChessMove** obstructedThreatMoves, int numObsMoves){
  ChessPiece* king = getPiece(*kingPos);
  Colour kingColour = king->getColour();
  ChessPosition* pos = new ChessPosition(0,0);
  ChessPiece* piece;


  do{
    piece = getPiece(*pos);
    // check if piece is same colour as king
    if(piece != nullptr && piece->getColour() == kingColour){
      // piece sits on the path of an obstructed
      for(int i = 0; i < numObsMoves; i++){
        if(pos->isPosinPath(obstructedThreatMoves[i]->getPath(), obstructedThreatMoves[i]->getSteps()-1)){

        }
      }
    }
  }while(pos->nextPosition());
  return false;
}

bool ChessBoard::isInStalemate(ChessPosition* kingPos){
  ChessPiece* king = getPiece(*kingPos);
  Colour kingColour = king->getColour();
  ChessPosition* strPos = new ChessPosition(0,0);
  ChessPiece* strPiece;
  ChessPosition* endPos = new ChessPosition(0,0);
  ChessPiece* endPiece;
  int steps;
  ChessPosition* obstructions[8];

  do{
    strPiece = getPiece(*strPos);
    if(strPiece != nullptr && strPiece->getColour() == kingColour){
      do{
        endPiece = getPiece(*endPos);
        if(endPiece != nullptr && endPiece->getColour() != kingColour){
          if(strPiece->validateMove(*strPos, *endPos, endPiece, steps, obstructions)){
            if(steps > 1 && !isMoveObstructed(steps, obstructions)){
              if(testMove(strPiece, *strPos, endPiece, *endPos, kingPos )){
                return false;
              }
            }
          }
        }
        else{
          if(strPiece->validateMove(*strPos, *endPos, endPiece, steps, obstructions)){
            if(steps > 1 && !isMoveObstructed(steps, obstructions)){
              if(testMove(strPiece, *strPos, endPiece, *endPos, kingPos)){
                return false;
              }
            }
          }
        }
      }while(endPos->nextPosition());
    }
  }while(strPos->nextPosition());
  return true;
}
