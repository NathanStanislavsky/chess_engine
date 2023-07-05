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

        int white_king_location = 60;
        int black_king_location = 4;

        vector<int> pieceCapturedLog;
        vector<Castling> castlingRightsLog;
        vector<int> enpassantSquareLog;
        vector<Move> moveLog;

        Pos(string fen);
        void printBoard();

        void doMove(Move move);

        void undoMove();

        bool inCheck(int targetSquare);

        void find_king_locations();
};