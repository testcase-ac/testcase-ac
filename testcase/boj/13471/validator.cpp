#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L: track length in decametres, must satisfy 1 <= L <= 1e6
    int L = inf.readInt(1, 1000000, "L");
    inf.readSpace();
    // Read S: maximal allowed distance between consecutive marshals,
    // must satisfy 1 <= S <= L (so S <= L)
    int S = inf.readInt(1, L, "S");
    // End of the single line
    inf.readEoln();
    // No further input
    inf.readEof();

    return 0;
}
