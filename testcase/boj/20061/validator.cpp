#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        int t = inf.readInt(1, 3, "t");
        inf.readSpace();
        int x = inf.readInt(0, 3, "x");
        inf.readSpace();
        int y = inf.readInt(0, 3, "y");
        inf.readEoln();

        if (t == 2) {
            // horizontal 1x2: (x, y), (x, y+1) must be within red 4x4 board
            ensuref(y + 1 <= 3, "Placement %d: horizontal block at (x=%d, y=%d) exceeds red board boundary (y+1 > 3)", i + 1, x, y);
        } else if (t == 3) {
            // vertical 2x1: (x, y), (x+1, y) must be within red 4x4 board
            ensuref(x + 1 <= 3, "Placement %d: vertical block at (x=%d, y=%d) exceeds red board boundary (x+1 > 3)", i + 1, x, y);
        }
        // t == 1: single 1x1, (x,y) already ensured in [0,3]
    }

    inf.readEof();
}
