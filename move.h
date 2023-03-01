#pragma once
#include <string>
using namespace std;

class Move {
    public:
        int fromSq;
        int toSq;
        int piece;

        int promotionType;
        bool isPromotion;

        bool isEnpassant;

        Move(int fSq, int tSq, int pieceParam, bool isEnp, int ptype, bool isProm);
};

string to_string(Move move);