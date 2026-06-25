#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIMIT = 1000000000000000000LL;
    const int MAX_CASES = 100000;

    for (int caseIndex = 1;; ++caseIndex) {
        setTestCase(caseIndex);

        long long lo = inf.readLong(0LL, LIMIT, "LO");
        inf.readSpace();
        long long hi = inf.readLong(0LL, LIMIT, "HI");
        inf.readSpace();
        int x = inf.readInt(0, 10, "X");
        inf.readEoln();

        if (lo == 0 && hi == 0 && x == 0) {
            break;
        }

        ensuref(lo >= 1, "LO must be at least 1, found %lld", lo);
        ensuref(lo <= hi, "LO must not exceed HI, found %lld > %lld", lo, hi);
        // CHECK: The statement gives no case-count limit; use the local default cap.
        ensuref(caseIndex <= MAX_CASES, "too many test cases: more than %d", MAX_CASES);
    }

    inf.readEof();
}
