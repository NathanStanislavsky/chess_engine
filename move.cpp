#include "move.h"


Move::Move(int fSq, int tSq, int pieceParam, bool isEnp, int ptype, bool isProm, bool isCas) {
    fromSq = fSq;
    toSq = tSq;
    piece = pieceParam;
    isEnpassant = isEnp;
    promotionType = ptype;
    isPromotion = isProm;
    isCastle = isCas;
}

string to_string(Move move) {
    return coords_to_square(move.fromSq) + coords_to_square(move.toSq);
}

int square_to_coords(string s) {
        return (s[0] - 'a') + (7-(s[1] - '1')) * 8;
    }

string coords_to_square(int index) {
    int row = index / 8;
    int col = index % 8;
    string result = "";
    result += ('a' + col);
    result += ('8' - row);
    return result;
}
