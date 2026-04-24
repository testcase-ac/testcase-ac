#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (true) {
        // Read n, the length of the sequence, or 0 to terminate.
        int n = inf.readInt(0, 100000, "n");
        inf.readEoln();

        // Terminator
        if (n == 0) break;

        // Count test cases and enforce the assumed upper bound on number of cases
        testCaseCount++;
        ensuref(testCaseCount <= 100000,
                "Number of test cases exceeds limit: %d > 100000",
                testCaseCount);

        // Read the sequence of length n, one integer per line.
        for (int i = 0; i < n; i++) {
            inf.readInt(1, 100, "a_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
