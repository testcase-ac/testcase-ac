#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    long long a = inf.readLong(1LL, 1000000000LL, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readSpace();
    long long x = inf.readLong(1LL, 1000000000LL, "X");
    inf.readSpace();
    long long y = inf.readLong(1LL, 1000000000LL, "Y");
    inf.readEoln();

    (void)a;
    (void)b;
    (void)x;
    (void)y;

    long long previousTime = 0;
    for (int i = 1; i <= n; ++i) {
        long long t = inf.readLong(1LL, 1000000000LL, "T_i");
        inf.readSpace();
        int s = inf.readInt(1, 3, "S_i");
        inf.readEoln();

        ensuref(previousTime < t,
                "T_i must be strictly increasing: T_%d=%lld, T_%d=%lld",
                i - 1, previousTime, i, t);
        previousTime = t;
        (void)s;
    }

    inf.readEof();
}
