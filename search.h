#pragma once
#include "pos.h"

int perft(Pos& pos, int depth, bool verbose);

Move getBestMove(Pos& pos, int depth);

int search(Pos& pos, int depth);

int eval(Pos& pos);
