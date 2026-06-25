#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "n");
    inf.readEoln();

    int positiveCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long value = inf.readLong(0LL, 1000000000LL, "a_ij");
            if (value > 0) {
                ++positiveCount;
            }

            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(positiveCount <= 5 * n,
            "number of positive entries must be at most 5n: positiveCount=%d, n=%d",
            positiveCount, n);

    inf.readEof();
}
