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

int negaMax(Pos& pos, int depth, int alpha, int beta) {
    if (depth == 0) return quiescence(pos, alpha, beta);
    int score = 0;
    int best_score = -MAX;
    vector<Move> movelist = generate_legal_moves(pos);

    if (movelist.size() == 0) {
        pos.find_king_locations();
        //checkmate
        if (pos.currentPlayer) {
            if (pos.inCheck(pos.white_king_location)) {
                return -MAX + 1;
            }
        } else {
            if (pos.inCheck(pos.black_king_location)) {
                return -MAX + 1;
            }
        }
        return 0;
    }

    for (int count = 0; count < movelist.size(); count++) {
        pos.doMove(movelist[count]);
        score = -negaMax(pos, depth - 1, -beta, -alpha);
        pos.undoMove();
        if (score > best_score) {
            best_score = score;
            if( score >= beta )
                return beta;   //  fail hard beta-cutoff
            if( score > alpha )
                alpha = score; // alpha acts like max in MiniMax
        }
    }
    return best_score;
}

int quiescence(Pos& pos, int alpha, int beta) {
    int best_score = eval(pos);
    if( best_score >= beta )
        return beta;
    if( alpha < best_score )
        alpha = best_score;
    vector<Move> moves = generate_legal_moves(pos);

    if (moves.size() == 0) {
        pos.find_king_locations();
        //checkmate
        if (pos.currentPlayer) {
            if (pos.inCheck(pos.white_king_location)) {
                return -MAX + 1;
            }
        } else {
            if (pos.inCheck(pos.black_king_location)) {
                return -MAX + 1;
            }
        }
        return 0;
    }

    for (int i = 0; i < moves.size(); i++) {
        if (pos.board_array[moves[i].toSq] != e) {
            pos.doMove(moves[i]);
            int score = -quiescence(pos, -beta, -alpha);
            pos.undoMove();

            if (score > best_score) {
                best_score = score;
                if( score >= beta )
                    return beta;
                if( score > alpha )
                    alpha = score;
            }
        }
    }
    return best_score;
}

Move get_best_move(Pos& pos, int depth) {
    Move best_move;
    int score = 0;
    int best_score = -MAX;
    vector<Move> movelist = generate_legal_moves(pos);
    for (int count = 0; count < movelist.size(); count++) {
        pos.doMove(movelist[count]);
        score = -negaMax(pos, depth - 1, -MAX, -best_score);
        cout << "Move: " << to_string(movelist[count]) << " score: " << score << endl;
        pos.undoMove();
        if (score > best_score) {
            best_move = movelist[count];
            best_score = score;
        }
    }
    return best_move;
}