#include "move.h"

string coords_to_square(int index);

Move::Move(int fSq, int tSq, int pieceParam, bool isEnp, int ptype, bool isProm) {
    fromSq = fSq;
    toSq = tSq;
    piece = pieceParam;
    isEnpassant = isEnp;
    promotionType = ptype;
    isPromotion = isProm;
}

string to_string(Move move) {
    return coords_to_square(move.fromSq) + coords_to_square(move.toSq);
}
