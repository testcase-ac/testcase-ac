#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of trenches
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Each trench is a segment with endpoints (X1, Y1) and (X2, Y2)
    for (int i = 0; i < N; i++) {
        int x1 = inf.readInt(0, 1000, "X1_" + to_string(i));
        inf.readSpace();
        int y1 = inf.readInt(0, 1000, "Y1_" + to_string(i));
        inf.readSpace();
        int x2 = inf.readInt(0, 1000, "X2_" + to_string(i));
        inf.readSpace();
        int y2 = inf.readInt(0, 1000, "Y2_" + to_string(i));
        inf.readEoln();
        // Degenerate segments (points) are allowed by statement
    }

    inf.readEof();
    return 0;
}
