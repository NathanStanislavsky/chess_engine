// loop through board and write if statements for each piece then push to vector if legal move
#include "moveGen.h"
using namespace std;

string coords_to_square(int index);

int startingWhiteKingPosition = 60;
int startingWhiteKingRookPosition = 63;
int startingWhiteQueenRookPosition = 56;
int startingBlackKingPosition = 4;
int startingBlackKingRookPosition = 7;
int startingBlackQueenRookPosition = 0;


bool pieceColor(int piece) {
    if (piece > 0 && piece < 7) {
        return true;
    } else if (piece > 6 && piece < 13) {
        return false;
    }
}

vector<Move> generate_psuedo_moves(Pos pos) {
    vector<Move> moves;
    moves.reserve(300);
    for (int square = 0; square < 64; square++) {
        int row = square / 8;
        int col = square % 8;
        int piece = pos.board_array[square];

        // proceed if piece is not empty and piece matches current color
        if (piece != e && pieceColor(piece) == pos.currentPlayer) {
            if (piece == P) {
                // Pawns can move forward one square if the square is empty
                if (pos.board_array[square - 8] == e && row != 1) {
                    moves.emplace_back(square, square - 8, pos.board_array[square]); 
                }
                if (row == 6 && pos.board_array[square - 8] == e && pos.board_array[square - 16] == e) {
                    moves.emplace_back(square, square - 16, pos.board_array[square]);
                }
                // Pawns can capture enemy pieces diagonally
                // left
                if (col > 0 && pos.board_array[square - 9] > 6 && row != 1) {
                    moves.emplace_back(square, square - 9, pos.board_array[square]);
                }
                // right
                if (col < 7 && pos.board_array[square - 7] > 6 && row != 1) {
                    moves.emplace_back(square, square - 7, pos.board_array[square]);
                }
                // enpassant left
                if (row == 3 && square - 9 == pos.enpassantSquare) {
                    moves.emplace_back(square, square - 9, true, pos.board_array[square]);
                }
                // enpassant right
                if (row == 3 && square - 7 == pos.enpassantSquare) {
                    moves.emplace_back(square, square - 7, true, pos.board_array[square]);
                }
                // promotion
                if (row == 1 && pos.board_array[square - 8] == e) {
                    moves.emplace_back(square, square - 8, R, true);
                    moves.emplace_back(square, square - 8, N, true);
                    moves.emplace_back(square, square - 8, B, true);
                    moves.emplace_back(square, square - 8, Q, true);
                }
                // promotion capture left
                if (row == 1 && pos.board_array[square - 9] > 6) {
                    moves.emplace_back(square, square - 9, R, true);
                    moves.emplace_back(square, square - 9, N, true);
                    moves.emplace_back(square, square - 9, B, true);
                    moves.emplace_back(square, square - 9, Q, true);
                }
                // promotion capture right
                if (row == 1 && pos.board_array[square - 7] > 6) {
                    moves.emplace_back(square, square - 7, R, true);
                    moves.emplace_back(square, square - 7, N, true);
                    moves.emplace_back(square, square - 7, B, true);
                    moves.emplace_back(square, square - 7, Q, true);
                }
            } else if (piece == p) {
                // Pawns can move forward one square if the square is empty
                if (pos.board_array[square + 8] == e && row != 6) {
                    moves.emplace_back(square, square + 8, pos.board_array[square]);
                }
                if (row == 1 && pos.board_array[square + 8] == e && pos.board_array[square + 16] == e) {
                    moves.emplace_back(square, square + 16, pos.board_array[square]);
                }
                // Pawns can capture enemy pieces diagonally
                // left
                if (col < 7 && pos.board_array[square + 9] > 0 && pos.board_array[square + 9] < 7 && row != 6) {
                    moves.emplace_back(square, square + 9, pos.board_array[square]);
                }
                // right
                if (col > 0 && pos.board_array[square + 7] > e && pos.board_array[square + 7] < p && row != 6) {
                    moves.emplace_back(square, square + 7, pos.board_array[square]);
                }
                // enpassant left
                if (row == 4 && square + 9 == pos.enpassantSquare) {
                    moves.emplace_back(square, square + 9, true, pos.board_array[square]);
                }
                // enpassant right
                if (row == 4 && square + 7 == pos.enpassantSquare) {
                    moves.emplace_back(square, square + 7, true, pos.board_array[square]);
                }
                // promotion
                if (row == 6 && pos.board_array[square + 8] == e) {
                    moves.emplace_back(square, square + 8, r, true);
                    moves.emplace_back(square, square + 8, n, true);
                    moves.emplace_back(square, square + 8, b, true);
                    moves.emplace_back(square, square + 8, q, true);
                }
                // promotion capture left
                if (row == 6 && pos.board_array[square + 7] > 0 && pos.board_array[square + 7] < 7) {
                    moves.emplace_back(square, square + 7, r, true);
                    moves.emplace_back(square, square + 7, n, true);
                    moves.emplace_back(square, square + 7, b, true);
                    moves.emplace_back(square, square + 7, q, true);
                }
                // promotion capture right
                if (row == 6 && pos.board_array[square + 9] > 0 && pos.board_array[square + 9] < 7) {
                    moves.emplace_back(square, square + 9, r, true);
                    moves.emplace_back(square, square + 9, n, true);
                    moves.emplace_back(square, square + 9, b, true);
                    moves.emplace_back(square, square + 9, q, true);
                }
            } else if (piece == N || piece == n) {
                int rowOffsets[] = {-2, -1, 1, 2, 2, 1, -1, -2};
                int colOffsets[] = {1, 2, 2, 1, -1, -2, -2, -1};
                for (int i = 0; i < 8; i++) {
                    int newRow = row + rowOffsets[i];
                    int newCol = col + colOffsets[i];
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        if (pos.board_array[newRow * 8 + newCol] == e || (piece == N && pos.board_array[newRow * 8 + newCol] > 6) || (piece == n && pos.board_array[newRow * 8 + newCol] < 7)) {
                            moves.emplace_back(square, newRow * 8 + newCol, pos.board_array[square]);
                        }
                    }
                }
            } else if (piece == R || piece == r) {
                // generate moves in the up direction
                for (int i = row - 1; i >= 0; i--) {
                    if (pos.board_array[i * 8 + col] == e) {
                        moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                    } else {
                        if (piece == R && (pos.board_array[i * 8 + col] > 6)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        } else if (piece == r && (pos.board_array[i * 8 + col] < 7)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the down direction
                for (int i = row + 1; i < 8; i++) {
                    if (pos.board_array[i * 8 + col] == e) {
                        moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                    } else {
                        if (piece == R && (pos.board_array[i * 8 + col] > 6)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        } else if (piece == r && (pos.board_array[i * 8 + col] < 7)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the left direction
                for (int i = col - 1; i >= 0; i--) {
                    if (pos.board_array[row * 8 + i] == e) {
                        moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                    } else {
                        if (piece == R && (pos.board_array[row * 8 + i] > 6)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        } else if (piece == r && (pos.board_array[row * 8 + i] < 7)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the right direction
                for (int i = col + 1; i < 8; i++) {
                    if (pos.board_array[row * 8 + i] == e) {
                        moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                    } else {
                        if (piece == R && (pos.board_array[row * 8 + i] > 6)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        } else if (piece == r && (pos.board_array[row * 8 + i] < 7)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        }
                        break;
                    }
                }
            } else if (piece == B || piece == b) {
                // generate moves in the top-left direction
                for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
                    if (pos.board_array[(row - i) * 8 + (col - i)] == e) {
                        moves.emplace_back(square, (row - i) * 8 + (col - i), pos.board_array[square]);
                    } else {
                        if (piece == B && (pos.board_array[(row - i) * 8 + (col - i)] > 6)) {
                            moves.emplace_back(square, (row - i) * 8 + (col - i), pos.board_array[square]);
                        } else if (piece == b && (pos.board_array[(row - i) * 8 + (col - i)] < 7)) {
                            moves.emplace_back(square, (row - i) * 8 + (col - i), pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the top-right direction
                for (int i = 1; row - i >= 0 && col + i < 8; i++) {
                    if (pos.board_array[(row - i) * 8 + (col + i)] == e) {
                        moves.emplace_back(square, (row - i) * 8 + (col + i), pos.board_array[square]);
                    } else {
                        if (piece == B && (pos.board_array[(row - i) * 8 + (col + i)] > 6)) {
                            moves.emplace_back(square, (row - i) * 8 + (col + i), pos.board_array[square]);
                        } else if (piece == b && (pos.board_array[(row - i) * 8 + (col + i)] < 7)) {
                            moves.emplace_back(square, (row - i) * 8 + (col + i), pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the bottom-left direction
                for (int i = 1; row + i < 8 && col - i >= 0; i++) {
                    if (pos.board_array[(row + i) * 8 + (col - i)] == e) {
                        moves.emplace_back(square, (row + i) * 8 + (col - i), pos.board_array[square]);
                    } else {
                        if (piece == B && (pos.board_array[(row + i) * 8 + (col - i)] > 6)) {
                            moves.emplace_back(square, (row + i) * 8 + (col - i), pos.board_array[square]);
                        } else if (piece == b && (pos.board_array[(row + i) * 8 + (col - i)] < 7)) {
                            moves.emplace_back(square, (row + i) * 8 + (col - i), pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the bottom-right direction
                for (int i = 1; row + i < 8 && col + i < 8; i++) {
                    if (pos.board_array[(row + i) * 8 + (col + i)] == e) {
                        moves.emplace_back(square, (row + i) * 8 + (col + i), pos.board_array[square]);
                    } else {
                        if (piece == B && (pos.board_array[(row + i) * 8 + (col + i)] > 6)) {
                            moves.emplace_back(square, (row + i) * 8 + (col + i), pos.board_array[square]);
                        } else if (piece == b && (pos.board_array[(row + i) * 8 + (col + i)] < 7)) {
                            moves.emplace_back(square, (row + i) * 8 + (col + i), pos.board_array[square]);
                        }
                        break;
                    }
                }
            } else if (piece == Q || piece == q) {
                // generate moves in the up direction
                for (int i = row - 1; i >= 0; i--) {
                    if (pos.board_array[i * 8 + col] == e) {
                        moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[i * 8 + col] > 6)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[i * 8 + col] < 7)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the down direction
                for (int i = row + 1; i < 8; i++) {
                    if (pos.board_array[i * 8 + col] == e) {
                        moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[i * 8 + col] > 6)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[i * 8 + col] < 7)) {
                            moves.emplace_back(square, i * 8 + col, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the left direction
                for (int i = col - 1; i >= 0; i--) {
                    if (pos.board_array[row * 8 + i] == e) {
                        moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[row * 8 + i] > 6)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[row * 8 + i] < 7)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the right direction
                for (int i = col + 1; i < 8; i++) {
                    if (pos.board_array[row * 8 + i] == e) {
                        moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[row * 8 + i] > 6)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[row * 8 + i] < 7)) {
                            moves.emplace_back(square, row * 8 + i, pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the top-left direction
                for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
                    if (pos.board_array[(row - i) * 8 + (col - i)] == e) {
                        moves.emplace_back(square, (row - i) * 8 + (col - i), pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[(row - i) * 8 + (col - i)] > 6)) {
                            moves.emplace_back(square, (row - i) * 8 + (col - i), pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[(row - i) * 8 + (col - i)] < 7)) {
                            moves.emplace_back(square, (row - i) * 8 + (col - i), pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the top-right direction
                for (int i = 1; row - i >= 0 && col + i < 8; i++) {
                    if (pos.board_array[(row - i) * 8 + (col + i)] == e) {
                        moves.emplace_back(square, (row - i) * 8 + (col + i), pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[(row - i) * 8 + (col + i)] > 6)) {
                            moves.emplace_back(square, (row - i) * 8 + (col + i), pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[(row - i) * 8 + (col + i)] < 7)) {
                            moves.emplace_back(square, (row - i) * 8 + (col + i), pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the bottom-left direction
                for (int i = 1; row + i < 8 && col - i >= 0; i++) {
                    if (pos.board_array[(row + i) * 8 + (col - i)] == e) {
                        moves.emplace_back(square, (row + i) * 8 + (col - i), pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[(row + i) * 8 + (col - i)] > 6)) {
                            moves.emplace_back(square, (row + i) * 8 + (col - i), pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[(row + i) * 8 + (col - i)] < 7)) {
                            moves.emplace_back(square, (row + i) * 8 + (col - i), pos.board_array[square]);
                        }
                        break;
                    }
                }
                // generate moves in the bottom-right direction
                for (int i = 1; row + i < 8 && col + i < 8; i++) {
                    if (pos.board_array[(row + i) * 8 + (col + i)] == e) {
                        moves.emplace_back(square, (row + i) * 8 + (col + i), pos.board_array[square]);
                    } else {
                        if (piece == Q && (pos.board_array[(row + i) * 8 + (col + i)] > 6)) {
                            moves.emplace_back(square, (row + i) * 8 + (col + i), pos.board_array[square]);
                        } else if (piece == q && (pos.board_array[(row + i) * 8 + (col + i)] < 7)) {
                            moves.emplace_back(square, (row + i) * 8 + (col + i), pos.board_array[square]);
                        }
                        break;
                    }
                }
            } else if (piece == K || piece == k) {
                // generate moves in the top-left direction
                if (row - 1 >= 0 && col - 1 >= 0) {
                    if ((pos.board_array[(row - 1) * 8 + (col - 1)] == e) || (piece == K && pos.board_array[(row - 1) * 8 + (col - 1)] > 6) || (piece == k && pos.board_array[(row - 1) * 8 + (col - 1)] < 7)) {
                        moves.emplace_back(square, (row - 1) * 8 + (col - 1), pos.board_array[square]);
                    }
                }
                // generate moves in the top direction
                if (row - 1 >= 0) {
                    if ((pos.board_array[(row - 1) * 8 + col] == e) || (piece == K && pos.board_array[(row - 1) * 8 + col] > 6) || (piece == k && pos.board_array[(row - 1) * 8 + col] < 7)) {
                        moves.emplace_back(square, (row - 1) * 8 + col, pos.board_array[square]);
                    }
                }
                // generate moves in the top-right direction
                if (row - 1 >= 0 && col + 1 < 8) {
                    if ((pos.board_array[(row - 1) * 8 + (col + 1)] == e) || (piece == K && pos.board_array[(row - 1) * 8 + (col + 1)] > 6) || (piece == k && pos.board_array[(row - 1) * 8 + (col + 1)] < 7)) {
                        moves.emplace_back(square, (row - 1) * 8 + (col + 1), pos.board_array[square]);
                    }
                }
                // generate moves in the right direction
                if (col + 1 < 8) {
                    if ((pos.board_array[row * 8 + (col + 1)] == e) || (piece == K && pos.board_array[row * 8 + (col + 1)] > 6) || (piece == k && pos.board_array[row * 8 + (col + 1)] < 7)) {
                        moves.emplace_back(square, row * 8 + (col + 1), pos.board_array[square]);
                    }
                }
                // generate moves in the bottom-right direction
                if (row + 1 < 8 && col + 1 < 8) {
                    if ((pos.board_array[(row + 1) * 8 + (col + 1)] == e) || (piece == K && pos.board_array[(row + 1) * 8 + (col + 1)] > 6) || (piece == k && pos.board_array[(row + 1) * 8 + (col + 1)] < 7)) {
                        moves.emplace_back(square, (row + 1) * 8 + (col + 1), pos.board_array[square]);
                    }
                }
                // generate moves in the bottom direction
                if (row + 1 < 8) {
                    if ((pos.board_array[(row + 1) * 8 + col] == e) || (row + 1 < 8 && piece == K && pos.board_array[(row + 1) * 8 + col] > 6) || (row + 1 < 8 && piece == k && pos.board_array[(row + 1) * 8 + col] < 7)) {
                        moves.emplace_back(square, (row + 1) * 8 + col, pos.board_array[square]);
                    }
                }
                // generate moves in the bottom-left direction
                if (row + 1 < 8 && col - 1 >= 0) {
                    if ((pos.board_array[(row + 1) * 8 + (col - 1)] == e) || (piece == K && pos.board_array[(row + 1) * 8 + (col - 1)] > 6) || (piece == k && pos.board_array[(row + 1) * 8 + (col - 1)] < 7)) {
                        moves.emplace_back(square, (row + 1) * 8 + (col - 1), pos.board_array[square]);
                    }
                }
                // generate moves in the left direction
                if (col - 1 >= 0) {
                    if ((pos.board_array[row * 8 + (col - 1)] == e) || (piece == K && pos.board_array[row * 8 + (col - 1)] > 6) || (piece == k && pos.board_array[row * 8 + (col - 1)] < 7)) {
                        moves.emplace_back(square, row * 8 + (col - 1), pos.board_array[square]);
                    }
                }

                // white king castle
                if (pos.currentPlayer && square == startingWhiteKingPosition && square + 3 == startingWhiteKingRookPosition && !pos.inCheck(square + 1) && !pos.inCheck(square + 2) && pos.board_array[square + 1] == e && pos.board_array[square + 2] == e) {
                    moves.emplace_back(square, square + 2, pos.board_array[square]);
                }

                // white queen castling
                if (pos.currentPlayer && square == startingWhiteKingPosition && square - 4 == startingWhiteQueenRookPosition && !pos.inCheck(square - 1) && !pos.inCheck(square - 2) && !pos.inCheck(square - 3) && pos.board_array[square - 1] == e && pos.board_array[square - 2] == e) {
                    moves.emplace_back(square, square - 2, pos.board_array[square]);
                }
                // black king castle
                if (!pos.currentPlayer && square == startingBlackKingPosition && square + 3 == startingBlackKingRookPosition && !pos.inCheck(square + 1) && !pos.inCheck(square + 2) && pos.board_array[square + 1] == e && pos.board_array[square + 2] == e) {
                    moves.emplace_back(square, square + 2, pos.board_array[square]);
                }

                // black queen castling
                if (!pos.currentPlayer && square == startingBlackKingPosition && square - 4 == startingBlackQueenRookPosition && !pos.inCheck(square - 1) && !pos.inCheck(square - 2) && !pos.inCheck(square - 3) && pos.board_array[square - 1] == e && pos.board_array[square - 2] == e) {
                    moves.emplace_back(square, square - 2, pos.board_array[square]);
                }
            }
        }
    }
    return moves;
}

vector<Move> generate_legal_moves(Pos pos) {
    vector<Move> psuedo_moves = generate_psuedo_moves(pos);
    vector<Move> legal_moves;
    // do move, generate opponenets psuedo moves, check if it can take king

    for (int i = 0; i < psuedo_moves.size(); i++) {
        pos.doMove(psuedo_moves[i]);
        // pos.printBoard();
        // cout << to_string(psuedo_moves[i]) << endl;
        vector<Move> oppsPsuedoMoves = generate_psuedo_moves(pos);
        // pos.printBoard();
        bool isKingSafe = true;
        for (int j = 0; j < oppsPsuedoMoves.size(); j++) {
            // cout << to_string(oppsPsuedoMoves[j]) << endl;

            if (pos.board_array[oppsPsuedoMoves[j].toSq] == K || pos.board_array[oppsPsuedoMoves[j].toSq] == k) {
                isKingSafe = false;
                // cout << "FUCKKKKK";
                break;
            }
        }
        if (isKingSafe) {
            legal_moves.push_back(psuedo_moves[i]);
        }
        pos.undoMove();
        // pos.printBoard();
    }
    return legal_moves;
}
