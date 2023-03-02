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
    Pos pos("r3k2r/Pppp1ppp/1b3nbN/nPB5/B1P1P3/q4N2/P2P2PP/b2Q1RK1 w kq - 0 2");
    pos.printBoard();
    
    cout << perft(pos, 1, true) << endl;

    return 0;   
}