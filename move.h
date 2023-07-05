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

        bool isCastle;
        Move(int fSq, int tSq, int pieceParam, bool isEnp, int ptype, bool isProm, bool isCas = false);
        Move();
};

string coords_to_square(int index);
int square_to_coords(string s);
string to_string(Move move);