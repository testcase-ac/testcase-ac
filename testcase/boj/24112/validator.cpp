#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int p = inf.readInt(1, 500000000, "P");
    inf.readEoln();

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int h = inf.readInt(1, 500000000, "h_k");
        inf.readEoln();
        sum += h;
        ensuref(sum <= 500000000LL,
                "sum of h_k exceeds 500000000 after index %d: %lld", i, sum);
    }

    inf.readEof();
}
