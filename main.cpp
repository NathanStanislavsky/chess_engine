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
    Pos pos("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    pos.printBoard();
    
    cout << perft(pos, 5, true) << endl;

    return 0;   
}