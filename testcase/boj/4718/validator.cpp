#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        long long lo = inf.readLong(0LL, 1000000000000000000LL, "LO");
        inf.readSpace();
        long long hi = inf.readLong(0LL, 1000000000000000000LL, "HI");
        inf.readSpace();
        int x = inf.readInt(0, 10, "X");
        inf.readEoln();

        if (lo == 0 && hi == 0 && x == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        // CHECK: The statement gives no testcase-count bound; use the local default cap.
        ensuref(caseCount <= 100000, "too many test cases");

        ensuref(1 <= lo, "LO must be at least 1, got %lld", lo);
        ensuref(lo <= hi, "LO must not exceed HI, got %lld > %lld", lo, hi);
    }

    inf.readEof();
}
