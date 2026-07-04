#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long b = inf.readLong(1LL, 1000000000LL, "b");
        inf.readSpace();
        long long e = inf.readLong(1LL, 1000000000LL, "e");
        inf.readSpace();
        inf.readInt(0, 1, "s");
        inf.readEoln();

        ensuref(b <= e, "question %d has b > e: %lld > %lld", i, b, e);
    }

    inf.readEof();
}
