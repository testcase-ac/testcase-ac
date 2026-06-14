#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement does not give an upper bound for T; use the local
    // practical cap for an unspecified number of independent test cases.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 15, "n");
        inf.readSpace();
        int h = inf.readInt(1, (1 << 30), "h");
        inf.readSpace();
        int o = inf.readInt(1, (1 << 30), "o");
        inf.readEoln();

        int houseCount = 1 << (2 * n);
        ensuref(h <= houseCount,
                "h must be a house number on an order-%d curve: h=%d, max=%d",
                n, h, houseCount);
        ensuref(o <= houseCount,
                "o must be a house number on an order-%d curve: o=%d, max=%d",
                n, o, houseCount);
    }

    inf.readEof();
}
