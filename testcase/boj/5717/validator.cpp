#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = 0;
    while (true) {
        // Read M and F, allowing 0 for the terminating case
        int M = inf.readInt(0, 5, "M_i");
        inf.readSpace();
        int F = inf.readInt(0, 5, "F_i");
        inf.readEoln();

        // Termination condition
        if (M == 0 && F == 0) {
            break;
        }

        // Non-terminating cases must satisfy 1 ≤ M, F ≤ 5
        testCount++;
        ensuref(M >= 1 && F >= 1,
                "Test case %d: M and F must be between 1 and 5, got M=%d, F=%d",
                testCount, M, F);
    }

    // The problem statement does not specify an explicit limit on the number
    // of test cases, so we enforce the default maximum of 100000.
    ensuref(testCount <= 100000,
            "Number of test cases (%d) exceeds the limit of 100000",
            testCount);

    inf.readEof();
    return 0;
}
