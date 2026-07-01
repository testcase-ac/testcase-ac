#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    string bits = inf.readToken("[01]{1,100000}", "B");
    ensuref((int)bits.size() == n, "B length must be N: got %d, expected %d",
            (int)bits.size(), n);
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "T");
        inf.readSpace();
        int l = inf.readInt(1, n, "L");
        inf.readSpace();
        int r = inf.readInt(1, n, "R");
        ensuref(l <= r, "query %d has L > R: %d > %d", i, l, r);
        inf.readEoln();
    }

    inf.readEof();
}
