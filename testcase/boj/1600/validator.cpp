#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(0, 30, "K");
    inf.readEoln();

    // Read W and H
    int W = inf.readInt(1, 200, "W");
    inf.readSpace();
    int H = inf.readInt(1, 200, "H");
    inf.readEoln();

    // Read the grid: H rows, each with W integers 0 or 1
    for (int i = 0; i < H; i++) {
        vector<int> row = inf.readInts(W, 0, 1, "grid");
        inf.readEoln();
        // Start (0,0) must be 0
        if (i == 0) {
            ensuref(row[0] == 0, "Start cell (0,0) must be 0, found %d", row[0]);
        }
        // End (H-1, W-1) must be 0
        if (i == H - 1) {
            ensuref(row[W - 1] == 0, "End cell (%d,%d) must be 0, found %d", H-1, W-1, row[W - 1]);
        }
    }

    inf.readEof();
    return 0;
}
