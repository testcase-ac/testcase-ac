#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement writes "1 <= t <= 10^4" for the first-line test
    // count, but per-case t is separately bounded by 10^9. Interpret this as T.
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readLong(1LL, 1000000000LL, "n");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "x");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "t");
        inf.readEoln();
    }

    inf.readEof();
}
