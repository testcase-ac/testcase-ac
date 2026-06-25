#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1 << 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20, "m");
    inf.readEoln();

    int upper = 1 << m;
    ensuref(n <= upper, "n must be at most 2^m: n=%d, m=%d", n, m);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, upper - 1, "a_i");
    }
    inf.readEoln();
    inf.readEof();
}
