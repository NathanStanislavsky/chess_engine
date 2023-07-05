// loop through board and write if statements for each piece then push to vector if legal move
#include "moveGen.h"
#include "cassert"
using namespace std;

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
    return false;
}

int upLeft(int square) {
    int newSquare = square - 9;
    assert(square >= 0 && square < 64);
    assert(newSquare >= 0 && newSquare < 64);
    return newSquare;
}

int upRight(int square) {
    int newSquare = square - 7;
    assert(square >= 0 && square < 64);
    assert(newSquare >= 0 && newSquare < 64);
    return newSquare;
}
int up(int square) {
    int newSquare = square - 8;
    assert(square >= 0 && square < 64);
    assert(newSquare >= 0 && newSquare < 64);
    return newSquare;
}
int downLeft(int square) {
    int newSquare = square + 7;
    assert(square >= 0 && square < 64);
    assert(newSquare >= 0 && newSquare < 64);
    return newSquare;
}

int downRight(int square) {
    int newSquare = square + 9;
    assert(square >= 0 && square < 64);
    assert(newSquare >= 0 && newSquare < 64);
    return newSquare;
}
int down(int square) {
    int newSquare = square + 8;
    assert(square >= 0 && square < 64);
    assert(newSquare >= 0 && newSquare < 64);
    return newSquare;
}

vector<Move> generate_psuedo_moves(Pos& pos) {
    
    vector<Move> moves;
    
    for (int square = 0; square < 64; square++) {
        int row = square / 8;
        int col = square % 8;
        int piece = pos.board_array[square];

        // proceed if piece is not empty and piece matches current color
        if (piece != e && pieceColor(piece) == pos.currentPlayer) {
            if (piece == P) {
                // Pawns can move forward one square if the square is empty
                if (pos.board_array[up(square)] == e && row != 1) {
                    moves.emplace_back(square, up(square), piece, false, piece, false); 
                }
                if (row == 6 && pos.board_array[up(square)] == e && pos.board_array[up(up(square))] == e) {
                    moves.emplace_back(square, up(up(square)), piece, false, piece, false);
                }
                // Pawns can capture enemy pieces diagonally
                // left
                if (col > 0 && pos.board_array[upLeft(square)] > 6 && row != 1) {
                    moves.emplace_back(square, upLeft(square), piece, false, piece, false);
                }
                // right
                if (col < 7 && pos.board_array[upRight(square)] > 6 && row != 1) {
                    moves.emplace_back(square, upRight(square), piece, false, piece, false);
                }
                // enpassant left
                if (row == 3 && upLeft(square) == pos.enpassantSquare) {
                    moves.emplace_back(square, upLeft(square), piece, true, piece, false);
                }
                // enpassant right
                if (row == 3 && upRight(square) == pos.enpassantSquare) {
                    moves.emplace_back(square, upRight(square), piece, true, piece, false);
                }
                // promotion
                if (row == 1 && pos.board_array[up(square)] == e) {
                    moves.emplace_back(square, up(square), piece, false, R, true);
                    moves.emplace_back(square, up(square), piece, false, N, true);
                    moves.emplace_back(square, up(square), piece, false, B, true);
                    moves.emplace_back(square, up(square), piece, false, Q, true);
                }
                // promotion capture left
                if (col > 0 && row == 1 && pieceColor(pos.board_array[upLeft(square)]) != pos.currentPlayer) {
                    moves.emplace_back(square, upLeft(square), piece, false, R, true);
                    moves.emplace_back(square, upLeft(square), piece, false, N, true);
                    moves.emplace_back(square, upLeft(square), piece, false, B, true);
                    moves.emplace_back(square, upLeft(square), piece, false, Q, true);
                }
                // promotion capture right
                if (col < 7 && row == 1 && pos.board_array[upRight(square)] > 6) {
                    moves.emplace_back(square, upRight(square), piece, false, R, true);
                    moves.emplace_back(square, upRight(square), piece, false, N, true);
                    moves.emplace_back(square, upRight(square), piece, false, B, true);
                    moves.emplace_back(square, upRight(square), piece, false, Q, true);
                }
            } else if (piece == p) {
                // Pawns can move forward one square if the square is empty
                if (pos.board_array[down(square)] == e && row != 6) {
                    moves.emplace_back(square, down(square), piece, false, piece, false);
                }
                if (row == 1 && pos.board_array[down(square)] == e && pos.board_array[down(down(square))] == e) {
                    moves.emplace_back(square, down(down(square)), piece, false, piece, false);
                }
                // Pawns can capture enemy pieces diagonally
                // left
                if (col < 7 && pos.board_array[downRight(square)] > 0 && pos.board_array[downRight(square)] < 7 && row != 6) {
                    moves.emplace_back(square, downRight(square), piece, false, piece, false);
                }
                // right
                if (col > 0 && pieceColor(pos.board_array[downLeft(square)]) != pos.currentPlayer && row != 6) {
                    moves.emplace_back(square, downLeft(square), piece, false, piece, false);
                }
                // enpassant left
                if (row == 4 && downRight(square) == pos.enpassantSquare) {
                    moves.emplace_back(square, downRight(square), piece, true, piece, false);
                }
                // enpassant right
                if (row == 4 && downLeft(square) == pos.enpassantSquare) {
                    moves.emplace_back(square, downLeft(square), piece, true, piece, false);
                }
                // promotion
                if (row == 6 && pos.board_array[down(square)] == e) {
                    moves.emplace_back(square, down(square), piece, false, r, true);
                    moves.emplace_back(square, down(square), piece, false, n, true);
                    moves.emplace_back(square, down(square), piece, false, b, true);
                    moves.emplace_back(square, down(square), piece, false, q, true);
                }
                // promotion capture left
                if (col < 7 && row == 6 && pos.board_array[downLeft(square)] > 0 && pos.board_array[downLeft(square)] < 7) {
                    moves.emplace_back(square, downLeft(square), piece, false, r, true);
                    moves.emplace_back(square, downLeft(square), piece, false, n, true);
                    moves.emplace_back(square, downLeft(square), piece, false, b, true);
                    moves.emplace_back(square, downLeft(square), piece, false, q, true);
                }
                // promotion capture right
                if (col > 0 && row == 6 && pos.board_array[downRight(square)] > 0 && pos.board_array[downRight(square)] < 7) {
                    moves.emplace_back(square, downRight(square), piece, false, r, true);
                    moves.emplace_back(square, downRight(square), piece, false, n, true);
                    moves.emplace_back(square, downRight(square), piece, false, b, true);
                    moves.emplace_back(square, downRight(square), piece, false, q, true);
                }
            } else if (piece == N || piece == n) {
                int rowOffsets[] = {-2, -1, 1, 2, 2, 1, -1, -2};
                int colOffsets[] = {1, 2, 2, 1, -1, -2, -2, -1};
                for (int i = 0; i < 8; i++) {
                    int newRow = row + rowOffsets[i];
                    int newCol = col + colOffsets[i];
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        if (pos.board_array[newRow * 8 + newCol] == e || (piece == N && pos.board_array[newRow * 8 + newCol] > 6) || (piece == n && pos.board_array[newRow * 8 + newCol] < 7)) {
                            moves.emplace_back(square, newRow * 8 + newCol, piece, false, piece, false);
                        }
                    }
                }
            } else if (piece == R || piece == r) {
                int row_off_sets[] = {-1, 0, 1, 0};
                int col_off_sets[] = {0, -1, 0, 1};

                for (int i = 0; i < 4; i++) {
                    for (int j = 1; j <= 8; j++) {
                        int end_row = row + row_off_sets[i] * j;
                        int end_col = col + col_off_sets[i] * j;

                        if (end_row >= 0 && end_row < 8 && end_col >= 0 && end_col < 8) {
                            if (pos.board_array[end_row * 8 + end_col] == e) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                            } else if (pieceColor(pos.board_array[end_row * 8 + end_col]) != pos.currentPlayer) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                                break;
                            } else {
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }
            } else if (piece == B || piece == b) {
                int bishop_row_off_sets[] = {-1, -1, 1, 1};
                int bishop_col_off_sets[] = {-1, 1, -1, 1};

                for (int i  = 0; i < 4; i++) {
                    for (int j = 1; j <= 8; j++) {
                        int end_row = row + bishop_row_off_sets[i] * j;
                        int end_col = col + bishop_col_off_sets[i] * j;

                        if (end_row >= 0 && end_row < 8 && end_col >= 0 && end_col < 8) {
                            if (pos.board_array[end_row * 8 + end_col] == e) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                            } else if (pieceColor(pos.board_array[end_row * 8 + end_col]) != pos.currentPlayer) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                                break;
                            } else {
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }
            } else if (piece == Q || piece == q) {
                int rook_row_off_sets[] = {-1, 0, 1, 0};
                int rook_col_off_sets[] = {0, -1, 0, 1};

                for (int i = 0; i < 4; i++) {
                    for (int j = 1; j <= 8; j++) {
                        int end_row = row + rook_row_off_sets[i] * j;
                        int end_col = col + rook_col_off_sets[i] * j;

                        if (end_row >= 0 && end_row < 8 && end_col >= 0 && end_col < 8) {
                            if (pos.board_array[end_row * 8 + end_col] == e) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                            } else if (pieceColor(pos.board_array[end_row * 8 + end_col]) != pos.currentPlayer) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                                break;
                            } else {
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }
                int bishop_row_off_sets[] = {-1, -1, 1, 1};
                int bishop_col_off_sets[] = {-1, 1, -1, 1};

                for (int i  = 0; i < 4; i++) {
                    for (int j = 1; j <= 8; j++) {
                        int end_row = row + bishop_row_off_sets[i] * j;
                        int end_col = col + bishop_col_off_sets[i] * j;

                        if (end_row >= 0 && end_row < 8 && end_col >= 0 && end_col < 8) {
                            if (pos.board_array[end_row * 8 + end_col] == e) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                            } else if (pieceColor(pos.board_array[end_row * 8 + end_col]) != pos.currentPlayer) {
                                moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                                break;
                            } else {
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }
            } else if (piece == K || piece == k) {
                int king_row_offsets[] = {1, 1, -1, -1, 0, 0, -1, 1};
                int king_col_offsets[] = {1, 0, -1, 0, 1, -1, 1, -1};

                for (int i = 0; i < 8; i++) {
                    int end_row = row + king_row_offsets[i];
                    int end_col = col + king_col_offsets[i];

                    if (end_row >= 0 && end_row < 8 && end_col >= 0 && end_col < 8) {
                        if (pos.board_array[end_row * 8 + end_col] == e && !pos.inCheck(end_row * 8 + end_col)) {
                            moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                        } else if (pieceColor(pos.board_array[end_row * 8 + end_col]) != pos.currentPlayer && !pos.inCheck(end_row * 8 + end_col)) {
                            moves.emplace_back(square, end_row * 8 + end_col, piece, false, piece, false);
                        }
                    }
                }

                // white king castle
                if (pos.currentPlayer && pos.cr.wkc && !pos.inCheck(square) && !pos.inCheck(square + 1) && !pos.inCheck(square + 2) && pos.board_array[square + 1] == e && pos.board_array[square + 2] == e && pos.board_array[square + 3] == R) {
                    moves.emplace_back(square, square + 2, piece, false, piece, false, true);
                }

                // white queen castling
                if (pos.currentPlayer && pos.cr.wqc && !pos.inCheck(square) && !pos.inCheck(square - 1) && !pos.inCheck(square - 2) && pos.board_array[square - 1] == e && pos.board_array[square - 2] == e && pos.board_array[square - 3] == e && pos.board_array[square - 4] == R) {
                    moves.emplace_back(square, square - 2, piece, false, piece, false, true);
                }
                // black king castle
                if (!pos.currentPlayer && pos.cr.bkc && !pos.inCheck(square) && !pos.inCheck(square + 1) && !pos.inCheck(square + 2) && pos.board_array[square + 1] == e && pos.board_array[square + 2] == e && pos.board_array[square + 3] == r) {
                    moves.emplace_back(square, square + 2, piece, false, piece, false, true);
                }

                // black queen castling
                if (!pos.currentPlayer && pos.cr.bqc && !pos.inCheck(square) && !pos.inCheck(square - 1) && !pos.inCheck(square - 2) && pos.board_array[square - 1] == e && pos.board_array[square - 2] == e && pos.board_array[square - 3] == e && pos.board_array[square - 4] == r) {
                    moves.emplace_back(square, square - 2, piece, false, piece, false, true);
                }
            }
        }
    }
    return moves;
}

vector<Move> generate_legal_moves(Pos& pos) {
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
