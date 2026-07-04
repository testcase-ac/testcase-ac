#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 10000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        long long n = inf.readLong(2LL, 1000000000000000000LL, "n");
        ensuref(n % 2 == 0, "n must be even, got %lld", n);
        inf.readEoln();
    }

    inf.readEof();
}
