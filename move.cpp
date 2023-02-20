#include "move.h"

string coords_to_square(int index);

Move::Move(int fSq, int tSq) {
    fromSq = fSq;
    toSq = tSq; 
}

Move::Move(int fSq, int tSq, int ptype, bool wprom, bool bprom) {
    fromSq = fSq;
    toSq = tSq;
    promotionType = ptype;
    isWhitePromotion = wprom;
    isBlackPromotion = bprom;
}

string to_string(Move move) {
    return coords_to_square(move.fromSq) + coords_to_square(move.toSq);
}
