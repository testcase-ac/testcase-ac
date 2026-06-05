#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const long long MAX_M = 1000000000LL;
    const long long MAX_Y = 1000000000LL;

    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();

    long long totalCows = 0;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(1LL, MAX_M, "x");
        inf.readSpace();
        long long y = inf.readLong(1LL, MAX_Y, "y");
        inf.readEoln();

        ensuref(totalCows <= MAX_M - x,
                "sum of cow counts exceeds 1,000,000,000 before line %d", i + 1);
        totalCows += x;
        (void)y;
    }

    ensuref(totalCows % 2 == 0, "total number of cows must be even: %lld", totalCows);
    // CHECK: The statement does not require distinct milk outputs across grouped lines.

    inf.readEof();
}
