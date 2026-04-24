#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of moves
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the move sequence: should be exactly N characters, each in '0'..'7'
    string moves = inf.readToken("[0-7]+", "moves");
    ensuref((int)moves.size() == N,
            "Length of moves sequence (%d) does not match N (%d)", (int)moves.size(), N);
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
