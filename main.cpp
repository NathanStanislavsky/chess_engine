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
    Pos pos("Q4rk1/5pp1/2Q1p3/3pP3/4b3/2P3pq/4PR1P/5RK1 b - - 0 34");
    pos.printBoard();
    Timestamp start = get_current_ms();

    cout << perft(pos, 2, true) << endl;
    
    print_time_diff(start);
    
    return 0;   
}