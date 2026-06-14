#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long unsigned32Max = 4294967295LL;
    const int maxCases = 100000; // CHECK: statement has no testcase-count limit; use local practical cap.

    int caseCount = 0;
    while (true) {
        long long m = inf.readLong(-unsigned32Max, unsigned32Max, "m");
        inf.readSpace();
        long long n = inf.readLong(-unsigned32Max, unsigned32Max, "n");
        inf.readEoln();

        if (m < 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);

        ensuref(caseCount <= maxCases, "too many test cases: %d", caseCount);
        ensuref(n >= 0, "n must be nonnegative for processed cases, got %lld", n);
        ensuref(m <= n, "m must be at most n, got %lld > %lld", m, n);
    }

    inf.readEof();
}
