#include <iostream>
#include "pos.h"
#include "move.h"
#include "moveGen.h"
#include "search.h"
#include <string>
#include <vector>
using namespace std;

int square_to_coords(string s) {
    return (s[0] - 'a') + (7-(s[1] - '1')) * 8;
}

string coords_to_square(int index) {
    int row = index / 8;
    int col = index % 8;
    return string(1, 'a' + col) + to_string(8 - row);
}

// main driver
int main()
{
    Pos pos("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
    pos.printBoard();
    
    cout << perft(pos, 2, true) << endl;

    return 0;
}