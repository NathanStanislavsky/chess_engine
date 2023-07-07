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
    Pos pos("Q4rk1/5pp1/2Q1p3/3pP3/4b3/2P4q/4PR1p/5RK1 w - - 0 35");
    pos.printBoard();
    Timestamp start = get_current_ms();
    // int think_time = 2000;
    // for (int depth_count = 1; think_time > get_time_diff(start); depth_count++) {
    //     cout << search(pos, depth_count) << endl;
    // }

    cout << perft(pos, 1, true) << endl;
    print_time_diff(start);
    
    return 0;   
}