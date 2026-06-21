#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int c = inf.readInt(1, n, "C");
    inf.readEoln();

    ensuref(n % 2 == 0, "N must be even, got %d", n);

    long long total = 0;
    for (int i = 1; i <= c; ++i) {
        int count = inf.readInt(0, n, "C_i");
        inf.readEoln();

        total += count;
        ensuref(count <= n / 2,
                "color %d has %d pearls, exceeding N/2=%d",
                i, count, n / 2);
    }

    ensuref(total == n, "sum of color counts must be N: got %lld, expected %d", total, n);

    inf.readEof();
}
