#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    long long l = inf.readLong(1LL, 1000000000LL, "L");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readSpace();
        long long b = inf.readLong(1LL, a, "b_i");
        inf.readSpace();
        long long d = inf.readLong(1LL, 1000000000LL, "d_i");
        inf.readEoln();

        ensuref((a - b) % d == 0,
                "a_i - b_i must be divisible by d_i at tire %d: a=%lld b=%lld d=%lld",
                i,
                a,
                b,
                d);
    }

    inf.readEof();
}
