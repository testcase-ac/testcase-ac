#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the three integers on the single input line
    int D = inf.readInt(5, 1000, "D");
    inf.readSpace();
    int H = inf.readInt(1, 99,   "H");
    inf.readSpace();
    int W = inf.readInt(2, 100,  "W");
    inf.readEoln();

    // Validate the ratio constraint H < W
    ensuref(H < W, "Invalid input: H (%d) must be less than W (%d)", H, W);

    // No more input
    inf.readEof();
    return 0;
}
