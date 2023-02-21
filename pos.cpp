// make method in position class to do move

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "pos.h"
#include "castling.h"
using namespace std;

int square_to_coords(string s);

map<char, Piece> whitePiece = {
    {'P', P},
    {'R', R},
    {'N', N},
    {'B', B},
    {'K', K},
    {'Q', Q}
};
map<char, Piece> blackPiece = {
    {'p', p},
    {'r', r},
    {'n', n},
    {'b', b},
    {'k', k},
    {'q', q}
};

map<Piece, char> pieceToChar = {
    {e, '-'},
    {P, 'P'},
    {R, 'R'},
    {N, 'N'},
    {B, 'B'},
    {K, 'K'},
    {Q, 'Q'},
    {p, 'p'},
    {r, 'r'},
    {n, 'n'},
    {b, 'b'},
    {k, 'k'},
    {q, 'q'}
}; 

Pos::Pos(string fen) {
    // initializes integer array to empty squares
    for (int i = 0; i < 64; i++) {
        board_array[i] = e;
    }
    // keeps track of current row and col
    int currentRow = 0;
    int currentCol = 0;

    // Split the FEN string into fields using the space character as a delimiter
    std::stringstream ss(fen);
    std::string field;
    std::vector<std::string> fields;
    while (std::getline(ss, field, ' ')) {
        fields.push_back(field);
    }

    std::string piecePlacement = fields[0];
    // parses fen string
    for (int i = 0; i < piecePlacement.size(); i++) {
        // white piece
        if (piecePlacement[i] >= 'A' && piecePlacement[i]<= 'Z') {
            board_array[currentRow * 8 + currentCol] = whitePiece[piecePlacement[i]];
            currentCol++;
        // black piece
        } else if (piecePlacement[i] >= 'a' && piecePlacement[i] <= 'z') {
            board_array[currentRow * 8 + currentCol] = blackPiece[piecePlacement[i]];
            currentCol++;
        // new line
        } else if (piecePlacement[i] == '/') {
            currentRow++;
            currentCol = 0;
        // empty square
        } else {
            // ascii math to determine number of empty squares
            int numEmptySquares = piecePlacement[i] - '0';
            // prints empty squares
            for (int j = 0; j < numEmptySquares; j++) {
                board_array[currentRow * 8 + currentCol] = e;
                currentCol++;
            }
        }
    }

    string activeColor = fields[1];
    if (activeColor == "w") {
        currentPlayer = 1;
    } else if (activeColor == "b") {
        currentPlayer = 0;
    }

    string castlingRights = fields[2];
    for (int i = 0; i < castlingRights.size(); i++) {
        if (castlingRights != "-") {
            for (int i = 0; i < castlingRights.size(); i++) {
                if (castlingRights[i] == 'K') {
                    cr.wkc = true;
                }
                if (castlingRights[i] == 'Q') {
                    cr.wqc = true;
                } 
                if (castlingRights[i] == 'k') {
                    cr.bkc = true;
                }
                if (castlingRights[i] == 'q') {
                    cr.bqc = true;
                }
            }
        }
    }

    string enpassantSq = fields[3];
    if (enpassantSq != "-") {
        enpassantSquare = square_to_coords(enpassantSq);

    } else {
        enpassantSquare = -1;
    }
}

void Pos::printBoard() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            cout << pieceToChar[(Piece)board_array[r*8+c]];
            cout << " ";
        }
        cout << "\n";
    }
}

void Pos::doMove(Move move) {
    pieceCapturedLog.push_back(board_array[move.toSq]);
    castlingRightsLog.push_back(Castling(cr.wkc, cr.wqc, cr.bkc, cr.bqc));
    enpassantSquareLog.push_back(enpassantSquare);
    moveLog.push_back(move);

    if (board_array[move.fromSq] == K) {
        cr.wkc = false;
        cr.wqc = false;
    }
    if (board_array[move.fromSq] == R && move.fromSq == 63) {
        cr.wkc = false;
    }
    if (board_array[move.fromSq] == R && move.fromSq == 56) {
        cr.wqc = false;
    }
    if (board_array[move.fromSq] == k) {
        cr.bkc = false;
        cr.bqc = false;
    }
    if (board_array[move.fromSq] == r && move.fromSq == 7) {
        cr.bkc = false;
    }
    if (board_array[move.fromSq] == r && move.fromSq == 0) {
        cr.bqc = false;
    }
    if (board_array[move.fromSq] == P && abs(move.fromSq - move.toSq) == 16) {
        // pawn moves two squares from starting position
        enpassantSquare = (move.fromSq + move.toSq) / 2;
    } else if (board_array[move.fromSq] == P && move.toSq == enpassantSquare) {
        // pawn captures en passant
        enpassantSquare = -1;
    } else {
        enpassantSquare = -1;
    }

    if (board_array[move.fromSq] == p && abs(move.fromSq - move.toSq) == 16) {
        // pawn moves two squares from starting position
        enpassantSquare = (move.fromSq + move.toSq) / 2;
    } else if (board_array[move.fromSq] == p && move.toSq == enpassantSquare) {
        // pawn captures en passant
        enpassantSquare = -1;
    } else {
        enpassantSquare = -1;
    }
    // pawn promtion
    if (board_array[move.fromSq] == P && move.fromSq/8 == 1 && move.toSq/8 == 0) {
        board_array[move.toSq] = board_array[move.promotionType];
        board_array[move.fromSq] = e;
        move.isWhitePromotion = true;
    } else if (board_array[move.fromSq] == p && move.fromSq/8 == 6 && move.toSq/8 == 7) {
        board_array[move.toSq] = board_array[move.promotionType];
        board_array[move.fromSq] = e;
        move.isBlackPromotion = true;
    } else {
        board_array[move.toSq] = board_array[move.fromSq];
        board_array[move.fromSq] = e;
    }
    currentPlayer = !currentPlayer;
}

void Pos::undoMove() {
    Move move = moveLog.back();

    moveLog.pop_back();

    cr = castlingRightsLog.back();

    castlingRightsLog.pop_back();

    enpassantSquare = enpassantSquareLog.back();

    enpassantSquareLog.pop_back();

    if (move.isWhitePromotion) {
        board_array[move.fromSq] = P;
        board_array[move.toSq] = e;
    } else if (move.isBlackPromotion) {
        board_array[move.fromSq] = p;
        board_array[move.toSq] = e;
    } else {
        board_array[move.fromSq] = board_array[move.toSq];
        board_array[move.toSq] = pieceCapturedLog.back();
    }
    
    pieceCapturedLog.pop_back();

    currentPlayer = !currentPlayer;
}

bool Pos::inCheck(int targetSquare) {
    int row = targetSquare / 8;
    int col = targetSquare % 8;

    // attack from up
    for (int i = row - 1; i >= 0; i--) {
        // checks if white
        if (currentPlayer) {
            if (board_array[i * 8 + col] != e && board_array[i * 8 + col] != r && board_array[i * 8 + col] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[i * 8 + col] != e && board_array[i * 8 + col] != R && board_array[i * 8 + col] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from down
    for (int i = row + 1; i < 8; i++) {
        if (currentPlayer) {
            if (board_array[i * 8 + col] != e && board_array[i * 8 + col] != r && board_array[i * 8 + col] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[i * 8 + col] != e && board_array[i * 8 + col] != R && board_array[i * 8 + col] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from left
    for (int i = col - 1; i >= 0; i--) {
        if (currentPlayer) {
            if (board_array[row * 8 + i] != e && board_array[row * 8 + i] != r && board_array[row * 8 + i] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[row * 8 + i] != e && board_array[row * 8 + i] != R && board_array[row * 8 + i] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from right
    for (int i = col + 1; i < 8; i++) {
        if (currentPlayer) {
            if (board_array[row * 8 + i] != e && board_array[row * 8 + i] != r && board_array[row * 8 + i] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[row * 8 + i] != e && board_array[row * 8 + i] != R && board_array[row * 8 + i] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from top left
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        if (currentPlayer) {
            if (board_array[(row - i) * 8 + (col - i)] != e && board_array[(row - i) * 8 + (col - i)] != b && board_array[(row - i) * 8 + (col - i)] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[(row - i) * 8 + (col - i)] != e && board_array[(row - i) * 8 + (col - i)] != B && board_array[(row - i) * 8 + (col - i)] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from top right
    for (int i = 1; row - i >= 0 && col + i < 8; i++) {
        if (currentPlayer) {
            if (board_array[(row - i) * 8 + (col + i)] != e && board_array[(row - i) * 8 + (col + i)] != b && board_array[(row - i) * 8 + (col + i)] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[(row - i) * 8 + (col + i)] != e && board_array[(row - i) * 8 + (col + i)] != B && board_array[(row - i) * 8 + (col + i)] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from bottom left
    for (int i = 1; row + i < 8 && col - i >= 0; i++) {
        if (currentPlayer) {
            if (board_array[(row + i) * 8 + (col - i)] != e && board_array[(row + i) * 8 + (col - i)] != b && board_array[(row + i) * 8 + (col - i)] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[(row + i) * 8 + (col - i)] != e && board_array[(row + i) * 8 + (col - i)] != B && board_array[(row + i) * 8 + (col - i)] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // attack from bottom right
    for (int i = 1; row + i < 8 && col + i < 8; i++) {
        if (currentPlayer) {
            if (board_array[(row + i) * 8 + (col + i)] != e && board_array[(row + i) * 8 + (col + i)] != b && board_array[(row + i) * 8 + (col + i)] != q) {
                break;
            } else {
                return true;
            }
        } else {
            if (board_array[(row + i) * 8 + (col + i)] != e && board_array[(row + i) * 8 + (col + i)] != B && board_array[(row + i) * 8 + (col + i)] != Q) {
                break;
            } else {
                return true;
            }
        }
    }
    // knight attack
    int rowOffsets[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int colOffsets[] = {1, 2, 2, 1, -1, -2, -2, -1};
    for (int i = 0; i < 8; i++) {
        int newRow = row + rowOffsets[i];
        int newCol = col + colOffsets[i];
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (currentPlayer) {
                if (board_array[newRow * 8 + newCol] == n) {
                    return true;
                }
            } else {
                if (board_array[newRow * 8 + newCol] == N) {
                    return true;
                }
            }
        }
    }

    // king adjacent
    int kingRowOffSets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int kingColOffSets[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int newRow = row + kingRowOffSets[i];
        int newCol = col + kingColOffSets[i];

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (currentPlayer) {
                if (board_array[newRow * 8 + newCol] == k) {
                    return true;
                }
            } else {
                if (board_array[newRow * 8 + newCol] == K) {
                    return true;
                }
            }
        }
    }

    // pawn
    if (currentPlayer) {
        if (board_array[targetSquare + 7] == p || board_array[targetSquare + 9] == p) {
            return true;
        }
    } else {
        if (board_array[targetSquare - 7] == P || board_array[targetSquare - 9] == P) {
            return true;
        }
    }
    

    return false;
}
