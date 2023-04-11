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

        pos.doMove(validMoves[i]);
        // if (depth == 1) {
        //     // cout << "after do move" << endl;
        //     // pos.printBoard();
        //     int temp1 = pos.board_array[4];
        //     cout << temp1 << endl;
        //     // cout << pos.cr.bkc + pos.cr.bqc<< endl;
        //     // cout << pos.inCheck(2) + pos.inCheck(3) + pos.inCheck(5) + pos.inCheck(6) << endl;
        // }
        

        int result = perft(pos, depth - 1, false);
        if (verbose) {
            cout << to_string(validMoves[i]) + " " + to_string(result) << endl;
        }
        count += result;
        pos.undoMove();
        // if (depth == 1) {
        //     // cout << "after undo" << endl;
        //     // pos.printBoard();
        //     int temp2 = pos.board_array[4];
        //     cout << temp2 << endl;
        //     // cout << pos.cr.bkc + pos.cr.bqc<< endl;
        //     // cout << pos.inCheck(2) + pos.inCheck(3) + pos.inCheck(5) + pos.inCheck(6) << endl;
        // }
        
        
    }
    return count;
}



