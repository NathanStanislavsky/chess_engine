#include <iostream>
#include "pos.h"
#include "move.h"
#include "moveGen.h"
#include "search.h"
#include <string>
#include <vector>
using namespace std;

// main driver
int main()
{
    Pos pos("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
    pos.printBoard();
    
    cout << perft(pos, 4, true) << endl;

    return 0;   
}