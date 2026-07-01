#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        long long a = inf.readLong(0LL, 4294967295LL, "A");
        inf.readSpace();
        long long b = inf.readLong(0LL, 4294967295LL, "B");
        inf.readSpace();
        long long c = inf.readLong(0LL, 4294967295LL, "C");
        inf.readSpace();
        int k = inf.readInt(0, 32, "k");
        inf.readEoln();

        if (a == 0 && b == 0 && c == 0 && k == 0) {
            break;
        }

        ++cases;
        // CHECK: The statement gives no instance count limit; cap inputs at a practical size.
        ensuref(cases <= 100000, "too many instances: %d", cases);
        ensuref(1 <= k && k <= 32, "k must be in [1, 32], got %d", k);

        long long limit = 1LL << k;
        ensuref(a < limit, "A must be less than 2^k, got A=%lld, k=%d", a, k);
        ensuref(b < limit, "B must be less than 2^k, got B=%lld, k=%d", b, k);
        ensuref(c < limit, "C must be less than 2^k, got C=%lld, k=%d", c, k);
    }

    inf.readEof();
}
