#include "search.h"
#include "pos.h"
#include "moveGen.h"
#include "move.h"
#include <vector>
#include <map>
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

int search(Pos& pos, int depth) {
    if (depth == 0) {
        return eval(pos);
    }

    vector<Move> list = generate_legal_moves(pos);
    int max = -10000;
    for (Move move : list) {
        pos.doMove(move);
        int eval = -search(pos, depth-1);
        pos.undoMove();

        if (eval > max) {
            max = eval;
        }
    }
    return max;
}

Move getBestMove(Pos& pos, int depth) {
    vector<Move> list = generate_legal_moves(pos);
    int max = -10000;
    Move bestMove = list[0];
    for (Move move : list) {
        pos.doMove(move);
        int eval = -search(pos, depth);
        pos.undoMove();

        if (eval > max) {
            max = eval;
            bestMove = move;
        }
    }

    return bestMove;
}



