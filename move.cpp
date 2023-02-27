#include "move.h"

string coords_to_square(int index);

Move::Move(int fSq, int tSq, int pieceParam) {
    fromSq = fSq;
    toSq = tSq; 
    isEnpassant = false;
    piece = pieceParam;
}

Move::Move(int fSq, int tSq, int ptype, bool isProm) {
    fromSq = fSq;
    toSq = tSq;
    isEnpassant = false;
    promotionType = ptype;
    isPromotion = isProm;
}

Move::Move(int fSq, int tSq, bool isEnp) {
    fromSq = fSq;
    toSq = tSq;
    isEnpassant = isEnp;
}

string to_string(Move move) {
    return coords_to_square(move.fromSq) + coords_to_square(move.toSq);
}
