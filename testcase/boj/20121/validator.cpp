#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 999999999, "N");
        inf.readSpace();
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readEoln();

        ensuref(n % 2 == 1, "N must be odd, got %d", n);
        ensuref(a != b, "A and B must be different, got %d", a);
    }

    inf.readEof();
}
