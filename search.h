#pragma once
#include "pos.h"
#include <string>
const int MAX = 100000000;

int perft(Pos& pos, int depth, bool verbose);

int eval(Pos& pos);

int negaMax(Pos& pos, int depth, int alpha, int beta);

int quiescence(Pos& pos, int alpha, int beta);

Move get_best_move(Pos& pos, int depth);