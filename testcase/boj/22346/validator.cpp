#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "q");
    inf.readEoln();

    long long length = 1;
    for (long long x = n; x > 1; x /= 2) {
        length = length * 2 + 1;
    }

    int totalK = 0;
    for (int query = 1; query <= q; ++query) {
        setTestCase(query);
        long long i = inf.readLong(1LL, length, "i");
        inf.readSpace();
        inf.readLong(i, length, "j");
        inf.readSpace();
        // CHECK: k is a count, so the unstated lower bound is zero.
        int k = inf.readInt(0, 10000, "k");
        inf.readEoln();
        totalK += k;
        ensuref(totalK <= 10000, "sum of k exceeds 10000 at query %d", query);
    }

    inf.readEof();
}
