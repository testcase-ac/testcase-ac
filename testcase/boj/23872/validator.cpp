#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 2, "T");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    long long previous_x = -1;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 10000, "y_i");
        inf.readEoln();

        ensuref(previous_x < x,
                "x_i must be strictly increasing at index %d: previous=%lld, current=%lld",
                i, previous_x, x);
        previous_x = x;
    }

    inf.readEof();
}
