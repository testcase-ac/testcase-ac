#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long x1 = inf.readLong(1LL, 1000000000LL, "x1");
        inf.readSpace();
        long long y1 = inf.readLong(1LL, 1000000000LL, "y1");
        inf.readSpace();
        long long x2 = inf.readLong(1LL, 1000000000LL, "x2");
        inf.readSpace();
        long long y2 = inf.readLong(1LL, 1000000000LL, "y2");
        inf.readEoln();

        ensuref(x1 != x2 || y1 != y2,
                "segment %d has identical endpoints: (%lld, %lld)",
                i,
                x1,
                y1);
    }

    inf.readEof();
}
