#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1024, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the initial N x N grid
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // grid values are natural numbers ≤ 1000
            inf.readInt(1, 1000, "grid_value");
            if (j < N) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    // Read M operations
    for (int i = 1; i <= M; i++) {
        int w = inf.readInt(0, 1, "w");
        inf.readSpace();
        if (w == 0) {
            // update: w x y c
            int x = inf.readInt(1, N, "x");
            inf.readSpace();
            int y = inf.readInt(1, N, "y");
            inf.readSpace();
            int c = inf.readInt(1, 1000, "c");
            inf.readEoln();
            // no further relations to check
        } else {
            // query: w x1 y1 x2 y2
            int x1 = inf.readInt(1, N, "x1");
            inf.readSpace();
            int y1 = inf.readInt(1, N, "y1");
            inf.readSpace();
            int x2 = inf.readInt(1, N, "x2");
            inf.readSpace();
            int y2 = inf.readInt(1, N, "y2");
            inf.readEoln();
            ensuref(x1 <= x2, "Operation %d: x1 (%d) must be ≤ x2 (%d)", i, x1, x2);
            ensuref(y1 <= y2, "Operation %d: y1 (%d) must be ≤ y2 (%d)", i, y1, y2);
        }
    }

    inf.readEof();
    return 0;
}
