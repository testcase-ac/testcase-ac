#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readEoln();

    // Read the bingo board
    for (int i = 0; i < n; i++) {
        // Each row has exactly m integers in [0,10000]
        inf.readInts(m, 0, 10000, "grid");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
