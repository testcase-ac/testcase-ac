#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        if (i + 1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    for (int qi = 0; qi < q; ++qi) {
        int t = inf.readInt(1, 4, "t");
        inf.readSpace();

        int l = inf.readInt(0, n - 1, "l");
        inf.readSpace();
        int r = inf.readInt(0, n - 1, "r");
        ensuref(l <= r, "query %d has l > r: %d > %d", qi + 1, l, r);

        if (t == 1) {
            inf.readSpace();
            inf.readInt(-10000, 10000, "c");
        } else if (t == 2) {
            inf.readSpace();
            inf.readLong(2LL, 1000000000LL, "d");
        }

        inf.readEoln();
    }

    inf.readEof();
}
