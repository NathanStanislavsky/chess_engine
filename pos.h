#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "move.h"
#include "castling.h"
#include <list>
using namespace std;

enum Piece {e, P, R, N, B, K, Q, p, r, n, b, k, q};

class Pos {
    public:
        int board_array[64];
        // 1 for white 0 for black
        int currentPlayer;
        // castling rights
        Castling cr;
        // enpassant square
        int enpassantSquare;

        list<int> pieceCapturedLog;
        list<Castling> castlingRightsLog;
        list<int> enpassantSquareLog;
        vector<Move> moveLog;

        Pos(string fen);
        void printBoard();

        void doMove(Move move);

        void undoMove();

        bool inCheck(int targetSquare);
};