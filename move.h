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

        Move(int fSq, int tSq, int ptype, bool isPromotion);

        Move(int fSq, int tSq, int pieceParam);

        Move(int fSq, int tSq, bool isEnp);
};

string to_string(Move move);