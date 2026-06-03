#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_N = 200000;
    constexpr int MAX_Q = 200000;
    constexpr long long MIN_COORD = -1000000000LL;
    constexpr long long MAX_COORD = 1000000000LL;

    int n = inf.readInt(2, MAX_N, "n");
    inf.readSpace();
    int q = inf.readInt(1, MAX_Q, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long x1 = inf.readLong(MIN_COORD, MAX_COORD, "x1");
        inf.readSpace();
        long long y1 = inf.readLong(MIN_COORD, MAX_COORD, "y1");
        inf.readSpace();
        long long x2 = inf.readLong(MIN_COORD, MAX_COORD, "x2");
        inf.readSpace();
        long long y2 = inf.readLong(MIN_COORD, MAX_COORD, "y2");
        inf.readEoln();

        // CHECK: The statement defines each station as a line segment with two endpoints.
        ensuref(x1 != x2 || y1 != y2, "station %d is a zero-length segment", i);
    }

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "query %d uses the same station twice: %d", i, a);
    }

    inf.readEof();
}
