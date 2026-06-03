#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d = inf.readInt(1, 200, "D");
    inf.readEoln();

    for (int tc = 1; tc <= d; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000000000, "m");
        inf.readEoln();

        ensuref(m <= n, "m must not exceed n: n=%d, m=%d", n, m);
    }

    inf.readEof();
}
