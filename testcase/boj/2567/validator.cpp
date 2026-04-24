#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of color papers: 1 <= n <= 100
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Each paper is placed with its lower-left corner at (x, y)
    // Papers are 10x10 and must lie entirely within a 100x100 canvas.
    // The problem statement gives x, y as natural numbers, and ensures papers
    // do not go out of the canvas, so 1 <= x, y <= 90.
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(1, 90, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 90, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
