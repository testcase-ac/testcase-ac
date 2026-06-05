#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long a = inf.readLong(0LL, 1000000000LL, "A");
        inf.readSpace();
        long long b = inf.readLong(0LL, 1000000000LL, "B");
        inf.readSpace();
        long long c = inf.readLong(0LL, 1000000000LL, "C");
        inf.readEoln();

        ensuref(a + b + c > 0, "A + B + C must be positive");
    }

    inf.readEof();
}
