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
    Pos pos("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ -");
    pos.printBoard();
    
    // string input;
    // cin >> input;
    // pos.doMove(Move(square_to_coords(input.substr(0,2)), square_to_coords(input.substr(2,4))));
    // pos.printBoard();

    cout << perft(pos, 4, true) << endl;

    // vector<Move> moves = generate_legal_moves(pos);
    // cout << moves.size() << endl;

    // for (int i = 0; i < moves.size(); i++) {
    //     cout << "Move from square " << coords_to_square(moves[i].fromSq) << " to square " << coords_to_square(moves[i].toSq) << endl;
    // }

    return 0;
}