#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 100000, "H");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "Q");
    inf.readSpace();
    int r = inf.readInt(1, 100000, "R");
    inf.readEoln();

    long long maxStart = 1LL * h * (h + 1) / 2;
    for (int i = 1; i <= q; ++i) {
        long long a = inf.readLong(1LL, maxStart, "drop_a");
        inf.readSpace();
        int b = inf.readInt(1, 100000, "drop_b");
        inf.readEoln();
    }

    for (int i = 1; i <= r; ++i) {
        int a = inf.readInt(1, h + 1, "query_a");
        inf.readSpace();
        int b = inf.readInt(a, h + 1, "query_b");
        inf.readEoln();
    }

    inf.readEof();
}
