#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxIndex = 1LL << 60;

    int m = inf.readInt(2, 24, "m");
    inf.readEoln();

    long long p = inf.readLong(1LL, maxIndex, "p");
    inf.readEoln();

    long long q = inf.readLong(1LL, maxIndex, "q");
    inf.readEoln();
    ensuref(p < q, "expected p < q, got p=%lld q=%lld", p, q);

    for (int i = 1; i <= m; ++i) {
        inf.readInt(0, 1999999999, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
