#pragma once
#include "pos.h"
#include <string>

int perft(Pos& pos, int depth, bool verbose);

int search(Pos& pos, int depth);

int eval(Pos& pos);

int negaMax(Pos& pos, int depth);

string get_best_move(Pos& pos, int depth);