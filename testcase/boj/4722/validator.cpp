#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    int totalPoints = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ensuref(n >= 2, "n must be 0 or between 2 and 1000, found %d", n);

        ++testCaseCount;
        ensuref(testCaseCount <= 100000,
                "too many test cases: %d", testCaseCount);

        totalPoints += n;
        // CHECK: The statement does not bound the number of cases; cap total
        // points to keep valid inputs within the local scalar-token limit.
        ensuref(totalPoints <= 2000000,
                "too many total points: %d", totalPoints);

        setTestCase(testCaseCount);
        for (int i = 0; i < n; ++i) {
            inf.readInt(-1000, 1000, "x");
            inf.readSpace();
            inf.readInt(-1000, 1000, "y");
            inf.readEoln();
            // CHECK: The statement does not say point locations are distinct,
            // so repeated coordinates are accepted.
        }
    }

    inf.readEof();
}
