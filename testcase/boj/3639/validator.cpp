#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readInt(1, n, "k");
    inf.readEoln();

    long long valueSum = 0;
    long long weightSum = 0;
    for (int i = 1; i <= n; ++i) {
        int v = inf.readInt(0, 1000000, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000, "w_i");
        inf.readEoln();

        valueSum += v;
        weightSum += w;
        ensuref(valueSum <= 10000000,
                "sum of v_i exceeds 10000000 after jewel %d: %lld",
                i,
                valueSum);
        ensuref(weightSum <= 10000000,
                "sum of w_i exceeds 10000000 after jewel %d: %lld",
                i,
                weightSum);
    }

    inf.readEof();
    return 0;
}
