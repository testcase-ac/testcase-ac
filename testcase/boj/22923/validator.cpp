#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n (number of circles), q (number of rectangles)
    int n = inf.readInt(1, 3000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 3000, "q");
    inf.readEoln();

    // Next n lines: x, y, r
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y_i");
        inf.readSpace();
        int r = inf.readInt(1, 1000000, "r_i");
        inf.readEoln();
        // No further constraints: overlapping / identical circles are allowed
    }

    // Next q lines: x, y, w, h
    for (int i = 0; i < q; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x_j");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y_j");
        inf.readSpace();
        int w = inf.readInt(1, 1000000, "w_j");
        inf.readSpace();
        int h = inf.readInt(1, 1000000, "h_j");
        inf.readEoln();
        // Rectangle is axis-aligned from (x, y) to (x + w, y + h)
        // No extra constraints needed (coordinates can go outside [-1e6,1e6])
    }

    inf.readEof();
}
