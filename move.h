#pragma once
#include <string>
using namespace std;

class Move {
    public:
        int fromSq;
        int toSq;

        int promotionType;
        bool isWhitePromotion; 
        bool isBlackPromotion;

        Move(int fSq, int tSq, int ptype, bool wprom, bool bprom);

        Move(int fSq, int tSq);
};

string to_string(Move move);