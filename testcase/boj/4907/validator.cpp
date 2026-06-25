#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = 0;
    while (true) {
        int n = inf.readInt(-1, 60, "N");
        inf.readSpace();

        if (n == -1) {
            inf.readInt(-1, -1, "R");
            inf.readSpace();
            inf.readInt(-1, -1, "S");
            inf.readSpace();
            inf.readInt(-1, -1, "E");
            inf.readEoln();
            break;
        }

        ++testCount;
        setTestCase(testCount);

        long long limit = (1LL << n) - 1;
        long long r = inf.readLong(0LL, limit, "R");
        inf.readSpace();
        long long s = inf.readLong(0LL, limit, "S");
        inf.readSpace();
        long long e = inf.readLong(0LL, limit, "E");
        inf.readEoln();

        ensuref(s <= e, "S must be at most E, got S=%lld and E=%lld", s, e);
        ensuref(e - s <= 10000LL,
                "E - S must be at most 10000, got S=%lld and E=%lld",
                s,
                e);

        // CHECK: The statement does not bound the number of test cases.
        ensuref(testCount <= 100000, "too many test cases: %d", testCount);
    }

    ensuref(testCount >= 1, "input must contain at least one test case");
    inf.readEof();
    return 0;
}
