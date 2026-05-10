#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: n, m, r
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 15, "m");
    inf.readSpace();
    int r = inf.readInt(1, 100, "r");
    inf.readEoln();

    // Read item counts
    inf.readInts(n, 1, 30, "t_i");
    inf.readEoln();

    // Read r roads
    for (int i = 0; i < r; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int l = inf.readInt(1, 15, "l_i");
        inf.readEoln();

        ensuref(a != b,
                "Loop detected at road index %d: (%d, %d)",
                i, a, b);
    }

    inf.readEof();
    return 0;
}
