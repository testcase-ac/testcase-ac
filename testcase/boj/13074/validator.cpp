#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        int n = inf.readInt(2, 100, "n");
        ensuref(n % 2 == 0, "n must be even, got %d", n);
        inf.readEoln();
    }

    inf.readEof();
}
