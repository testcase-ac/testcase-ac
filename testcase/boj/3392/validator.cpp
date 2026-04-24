#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of rectangles
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // For each rectangle, read and validate coordinates
    for (int i = 1; i <= N; i++) {
        int x1 = inf.readInt(0, 30000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, 30000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, 30000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, 30000, "y2");
        inf.readEoln();

        // Ensure non-degeneracy: x1 < x2 and y1 < y2
        ensuref(x1 < x2,
                "Rectangle %d invalid: x1 (%d) is not less than x2 (%d)",
                i, x1, x2);
        ensuref(y1 < y2,
                "Rectangle %d invalid: y1 (%d) is not less than y2 (%d)",
                i, y1, y2);
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
