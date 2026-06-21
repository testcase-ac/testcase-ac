#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    for (int t = 1; t <= c; ++t) {
        setTestCase(t);

        long long a = inf.readLong(1LL, 1000000000000LL, "A");
        inf.readSpace();
        long long b = inf.readLong(a, 1000000000000LL, "B");
        inf.readSpace();
        long long p = inf.readLong(2LL, b, "P");
        inf.readEoln();

        ensuref(b <= a + 1000000LL,
                "interval width too large: A=%lld, B=%lld", a, b);
    }

    inf.readEof();
}
