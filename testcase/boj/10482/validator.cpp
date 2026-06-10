#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        int x = inf.readInt(4, 32000, "x");
        inf.readEoln();
        ensuref(x % 2 == 0, "x must be even, got %d", x);
    }

    inf.readEof();
}
