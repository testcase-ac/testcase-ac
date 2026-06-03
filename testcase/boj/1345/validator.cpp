#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMinValue = -1000000;
    constexpr int kMaxValue = 1000000;

    int n = inf.readInt(0, 50, "N");
    inf.readSpace();
    inf.readInt(kMinValue, kMaxValue, "A_0");
    inf.readEoln();

    if (n > 0) {
        auto s = inf.readInts(n, kMinValue, kMaxValue, "S_i");
        inf.readEoln();

        for (int i = 1; i < n; ++i) {
            ensuref(s[i - 1] <= s[i], "S must be nondecreasing: S_%d=%d > S_%d=%d",
                    i - 1, s[i - 1], i, s[i]);
        }
    }

    inf.readEof();
}
