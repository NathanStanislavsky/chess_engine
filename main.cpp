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
    Pos pos("4rk2/8/2R5/p5n1/3B4/1P2P3/P3K3/8 w - - 0 40");
    pos.printBoard();
    Timestamp start = get_current_ms();
    cout << eval(pos) << endl;
    cout << search(pos, 4) << endl;
    print_time_diff(start);
    
    return 0;   
}