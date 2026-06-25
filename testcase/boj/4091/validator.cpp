#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        // CHECK: The statement does not give a maximum number of test cases.
        ensuref(caseCount < 100000, "too many test cases");

        int n = inf.readInt(0, 1000, "N");
        inf.readSpace();
        int a = inf.readInt(0, 10000, "A");
        inf.readSpace();
        int b = inf.readInt(0, 10000, "B");
        inf.readEoln();

        if (n == 0 && a == 0 && b == 0) {
            // CHECK: A terminator-only file has no problem instance.
            ensuref(caseCount > 0, "input must contain at least one test case");
            break;
        }

        ensuref(n >= 1, "N must be at least 1 in a test case, got %d", n);
        ++caseCount;
        setTestCase(caseCount);

        int capacity = a + b;
        int totalNeeded = 0;
        for (int i = 1; i <= n; ++i) {
            // CHECK: The statement omits an explicit K bound; allow zero demand
            // and use the stated sum(K) <= A+B guarantee as the effective cap.
            int k = inf.readInt(0, capacity, "K");
            inf.readSpace();
            int da = inf.readInt(0, 1000, "DA");
            inf.readSpace();
            int db = inf.readInt(0, 1000, "DB");
            inf.readEoln();

            totalNeeded += k;
            ensuref(totalNeeded <= capacity,
                    "sum of K exceeds A+B in case %d after team %d: %d > %d",
                    caseCount, i, totalNeeded, capacity);
        }
    }

    inf.readEof();
}
