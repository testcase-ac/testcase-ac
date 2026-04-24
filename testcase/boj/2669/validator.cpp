#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly four rectangles
    for (int i = 0; i < 4; i++) {
        // Read bottom-left and top-right coordinates
        int x1 = inf.readInt(1, 100, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 100, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, 100, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 100, "y2");
        inf.readEoln();

        // Ensure non-degenerate rectangle
        ensuref(x1 < x2,
                "Rectangle %d: x1 (%d) must be strictly less than x2 (%d)",
                i+1, x1, x2);
        ensuref(y1 < y2,
                "Rectangle %d: y1 (%d) must be strictly less than y2 (%d)",
                i+1, y1, y2);
    }

    inf.readEof();
    return 0;
}
