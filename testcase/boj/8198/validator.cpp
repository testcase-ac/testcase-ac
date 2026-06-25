#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "k");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
    inf.readEoln();

    long long previous = 0;
    for (int i = 1; i <= n; ++i) {
        long long p = inf.readLong(1LL, 1000000000000000000LL, "p_i");
        ensuref(previous < p, "positions must be strictly increasing at index %d", i);
        previous = p;

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
