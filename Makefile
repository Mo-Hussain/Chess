OBJ = ChessMain.o ChessBoard.o ChessPiece.o Bishop.o King.o Pawn.o Queen.o Rook.o Knight.o ChessPosition.o ChessMove.o
EXE = chess
CXX = g++
CXXFLAGS = -std=c++11

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -g $< -o $@

-include $(OBJ:.o=.d)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXE)
