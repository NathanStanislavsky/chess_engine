#pragma once
#include <vector>
#include "pos.h"
#include "move.h"
#include "castling.h"

using namespace std;

bool pieceColor(Piece piece);

vector<Move> generate_psuedo_moves(Pos pos);

vector<Move> generate_legal_moves(Pos pos);