#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalWindow = 0;
    int caseCount = 0;

    while (true) {
        long long a = inf.readLong(0LL, 1000000000000LL, "a");
        if (a == 0) {
            inf.readEoln();
            break;
        }

        inf.readSpace();
        long long b = inf.readLong(0LL, 1000000000000LL, "b");
        inf.readSpace();
        long long l = inf.readLong(0LL, 1000000000000LL, "L");
        inf.readSpace();
        long long u = inf.readLong(0LL, 1000000000000LL, "U");
        inf.readEoln();

        ++caseCount;
        setTestCase(caseCount);

        ensuref(l <= u, "expected L <= U, got L=%lld and U=%lld", l, u);
        ensuref(u - l <= 1000000LL, "expected U - L <= 1000000, got %lld", u - l);

        __int128 value = static_cast<__int128>(a) * u + b;
        ensuref(value <= 1000000000000LL, "expected a * U + b <= 10^12");

        // CHECK: The statement has no case-count or aggregate-work limit; cap
        // them locally to keep sentinel-style inputs finite and practical.
        ensuref(caseCount <= 100000, "too many cases: %d", caseCount);
        totalWindow += u - l + 1;
        ensuref(totalWindow <= 1000001LL,
                "sum of interval lengths exceeds the local practical cap");
    }

    inf.readEof();
}
