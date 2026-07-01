#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCases = 100000;
    const int maxTotalIntervals = 1000000;
    // CHECK: The statement gives no endpoint bound; cap positive integer times at a conventional int-scale limit.
    const int maxEndpoint = 1000000000;

    int cases = 0;
    int totalIntervals = 0;
    while (true) {
        int n = inf.readInt(0, 50, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        ++cases;
        // CHECK: The statement has no case-count bound; cap cases and aggregate intervals for practical validation.
        ensuref(cases <= maxCases, "too many test cases: %d", cases);
        totalIntervals += n;
        ensuref(totalIntervals <= maxTotalIntervals,
                "too many total intervals: %d", totalIntervals);

        setTestCase(cases);
        for (int i = 1; i <= n; ++i) {
            int a = inf.readInt(1, maxEndpoint, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, maxEndpoint, "b_i");
            inf.readEoln();
            ensuref(a < b, "interval %d has start %d not less than end %d", i, a, b);
        }
    }

    ensuref(cases > 0, "at least one test case is required before the terminating 0");
    inf.readEof();
}
