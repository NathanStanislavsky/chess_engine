#include "search.h"
#include "pos.h"
#include "moveGen.h"
#include "move.h"
#include <vector>

int perft(Pos pos, int depth, bool verbose) {
    if (depth == 0) {
        return 1;
    }

    vector<Move>* validMoves = new vector<Move>(generate_legal_moves(pos));
    int count = 0;
    // iterate through valid Moves
    for (int i = 0; i < validMoves->size(); i++) {
        pos.doMove((*validMoves)[i]);
        int result = perft(pos, depth - 1, false);
        if (verbose) {
            cout << to_string((*validMoves)[i]) + " " + to_string(result) << endl;
        }
        count += result;
        pos.undoMove();
    }
    delete validMoves;

    return count;
}


