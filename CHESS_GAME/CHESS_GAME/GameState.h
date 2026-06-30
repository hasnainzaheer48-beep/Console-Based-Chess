#pragma once
#include"Board.h"
#include"FileLogger.h"
class GameState {
private:
    Board board;
    char currentTurn;         // 'W' or 'B'
    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteRookAMoved;
    bool whiteRookHMoved;
    bool blackRookAMoved;
    bool blackRookHMoved;
    int prevSrcRow;
    int prevSrcCol;
    int prevDstRow;
    int prevDstCol;
    char prevPiece;
    FileLogger log;
    

public:
    void startGame();
    void switchTurn();
    bool isInCheck(char color , Board& tempboard);
    bool isCheckmate(char color , Board& board);
    bool isStalemate(char color , Board& board);
    bool isLegalMove(int srcRow, int srcCol, int dstRow, int dstCol);
    int convert(char coordinate);
    int convert(int cdn);
    void PawnPromotion( char Symb, int dstRow, int dstCol);
    bool EnPassant(int srcRow, int srcCol, int dstRow, int dstCol);
    bool Castling(int srcRow, int srcCol, int dstRow, int dstCol);
    GameState();
};
