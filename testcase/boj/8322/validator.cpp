#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int k = inf.readInt(0, 1000000000, "K");
        inf.readSpace();
        int n = inf.readInt(0, 1000000000, "N");
        inf.readSpace();
        int x1 = inf.readInt(-1000000000, 1000000000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-1000000000, 1000000000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-1000000000, 1000000000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-1000000000, 1000000000, "y2");
        inf.readEoln();

        ensuref(k + n > 0, "K + N must be positive, got K=%d and N=%d", k, n);
        (void)x1;
        (void)y1;
        (void)x2;
        (void)y2;
    }

    inf.readEof();
}
