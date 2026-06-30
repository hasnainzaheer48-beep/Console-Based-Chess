#pragma once
#include<fstream>

using namespace std;


class FileLogger {
private:
    int moveNumber;
    ofstream file;
public:
    FileLogger();
    void logMove(char player, char piece,int srcRow, int srcCol,int dstRow,
                int dstCol,bool isCapture, bool isEnPassant,bool isCastling,
                bool isPromotion, bool isCheck);
    void logResignation(char color);
    void logCheckmate(char color);
    void logStalemate(char color);
    
};
