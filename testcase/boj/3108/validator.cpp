#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of rectangles
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read each rectangle
    for (int i = 0; i < N; i++) {
        int x1 = inf.readInt(-500, 500, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-500, 500, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-500, 500, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-500, 500, "y2");
        inf.readEoln();

        ensuref(x1 < x2,
                "Rectangle %d: x1 (%d) must be less than x2 (%d)", i+1, x1, x2);
        ensuref(y1 < y2,
                "Rectangle %d: y1 (%d) must be less than y2 (%d)", i+1, y1, y2);
    }

    inf.readEof();
    return 0;
}
