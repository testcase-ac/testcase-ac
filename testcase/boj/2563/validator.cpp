#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of color papers: at least 1, at most 100
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // For each paper, read the lower-left corner (x, y)
    // They are given as natural numbers and the 10x10 paper must lie entirely within the 100x100 canvas.
    // Hence 1 <= x, y <= 90.
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(1, 90, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 90, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
