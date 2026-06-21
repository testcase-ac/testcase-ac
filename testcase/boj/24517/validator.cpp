#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        long long a = inf.readLong(1LL, 1000000000LL, "A");
        inf.readSpace();
        long long b = inf.readLong(1LL, 1000000000LL, "B");
        inf.readSpace();
        inf.readInt(1, 10, "K");
        inf.readEoln();

        ensuref(a < b, "A must be less than B: A=%lld, B=%lld", a, b);
    }

    inf.readEof();
}
