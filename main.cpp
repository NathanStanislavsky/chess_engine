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
    Pos pos("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    pos.printBoard();
    Timestamp start = get_current_ms();
    cout << perft(pos, 5, true) << endl;
    print_time_diff(start);
    
    return 0;   
}