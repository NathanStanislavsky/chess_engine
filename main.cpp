#include <iostream>
#include "pos.h"
#include "move.h"
#include "moveGen.h"
#include "search.h"
#include <string>
#include <vector>
#include "timer.h"
using namespace std;

// main driver
int main()
{
    Pos pos("8/pk3B2/4Q3/bNp2p2/2P3bK/3r4/PP6/R4R2 b - - 13 54");
    pos.printBoard();
    Timestamp start = get_current_ms();
    int think_time = 10000;
    for (int depth = 1; think_time > get_time_diff(start); depth++) {
        cout << "depth: " << depth << " best_move: " << to_string(get_best_move(pos, depth)) << endl;
    }
    print_time_diff(start);
    
    return 0;   
}