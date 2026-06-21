#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        int x = inf.readInt(-1200, 1200, "x");
        inf.readSpace();
        int y = inf.readInt(-1200, 1200, "y");
        inf.readSpace();
        int k = inf.readInt(-1200, 1200, "k");
        inf.readEoln();

        ensuref(x <= k, "expected x <= k, got x=%d, k=%d", x, k);
        ensuref(k <= y, "expected k <= y, got k=%d, y=%d", k, y);
    }

    inf.readEof();
}
