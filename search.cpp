#include "search.h"
#include "pos.h"
#include "moveGen.h"
#include "move.h"
#include <vector>
using namespace std;

int perft(Pos pos, int depth, bool verbose) {
    if (depth == 0) {
        return 1;
    }
    // if (depth == 1) {
    //     pos.printBoard();
    // }

    vector<Move> validMoves = generate_legal_moves(pos);
    int count = 0;
    // iterate through valid Moves
    for (int i = 0; i < validMoves.size(); i++) {
        // cout << "before move" << endl;
        pos.doMove(validMoves[i]);
        // cout << "after move" << endl;
        int result = perft(pos, depth - 1, false);
        if (verbose) {
            cout << to_string(validMoves[i]) + " " + to_string(result) << endl;
        }
        count += result;
        // cout << "before undo move" << endl;
        pos.undoMove();
        // cout << "after undo move" << endl;
        
    }
    return count;
}


