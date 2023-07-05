#include "search.h"
#include "pos.h"
#include "moveGen.h"
#include "move.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

map<int, int> pointValue = {
    {R, 500},
    {B, 300},
    {N, 300},
    {Q, 900},
    {K, 100},
    {P, 100},
    {r, 500},
    {b, 300},
    {n, 300},
    {q, 900},
    {k, 100},
    {p, 100}
};

int perft(Pos& pos, int depth, bool verbose) {
    if (depth == 0) {
        return 1;
    }

    vector<Move> validMoves = generate_legal_moves(pos);
    int count = 0;
    // iterate through valid Moves
    for (int i = 0; i < validMoves.size(); i++) {

        pos.doMove(validMoves[i]);

        int result = perft(pos, depth - 1, false);
        if (verbose) {
            cout << to_string(validMoves[i]) + " " + to_string(result) << endl;
        }
        count += result;
        pos.undoMove();
        
        
        
    }
    return count;
}



int eval(Pos& pos) {
    int currentPlayerMaterial = 0;
    int opponentPlayerMaterial = 0;

    for (int i = 0; i < 64; i++) {
        int pc= pos.board_array[i];
        if (pc != e) {
            if (pieceColor(pc) == pos.currentPlayer) {
                currentPlayerMaterial += pointValue[pc];
            } else {
                opponentPlayerMaterial += pointValue[pc];
            }
        }
    }
    return currentPlayerMaterial - opponentPlayerMaterial;
}


int negaMax(Pos pos, int depth) {  // Updated function implementation
    int score = 0;
    if (depth == 0) return eval(pos);
    int max = -500000000;
    vector<Move> movelist = generate_legal_moves(pos);
    for (int count = 0; count < movelist.size(); count++) {
        score = -negaMax(pos, depth - 1);
        if (score > max)
            max = score;
    }
    return max;
}

int search(Pos& pos, int depth) {
    return negaMax(pos, depth);  // Update the function call to use negaMax
}

