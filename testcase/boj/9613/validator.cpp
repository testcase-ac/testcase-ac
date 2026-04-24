#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; tc++) {
        // mark the current test case for clearer error messages
        setTestCase(tc);

        // Read n (number of integers in this test case)
        // Constraint: 1 < n <= 100
        int n = inf.readInt(2, 100, "n");
        // Exactly one space before the first element
        inf.readSpace();

        // Read the n positive integers, each in [1, 1e6]
        for (int i = 0; i < n; i++) {
            inf.readInt(1, 1000000, "a_i");
            if (i + 1 < n) {
                // exactly one space between numbers
                inf.readSpace();
            }
        }

        // End of this test case line
        inf.readEoln();
    }

    // No extra data after all test cases
    inf.readEof();
    return 0;
}
