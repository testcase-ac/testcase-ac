#include "testlib.h"

#include <cstdlib>

using namespace std;

int manhattan(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 3000, "M");
    inf.readEoln();

    int k = inf.readInt(1, 3000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int r = inf.readInt(1, n, "R_i");
        inf.readSpace();
        int c = inf.readInt(1, m, "C_i");
        inf.readSpace();
        int d = inf.readInt(0, 3000, "D_i");
        inf.readEoln();

        ensuref(manhattan(r, c, 1, 1) > d,
                "zone %d blocks start: R=%d C=%d D=%d", i, r, c, d);
        ensuref(manhattan(r, c, n, m) > d,
                "zone %d blocks school: R=%d C=%d D=%d", i, r, c, d);
    }

    inf.readEof();
}
