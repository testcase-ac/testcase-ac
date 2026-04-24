#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    // Process each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N: number of natural numbers in this test
        int N = inf.readInt(1, 100, "N");
        inf.readEoln();

        // Read the N natural numbers, each between 1 and 10 inclusive,
        // with exactly one space between them, and then end-of-line.
        for (int i = 0; i < N; i++) {
            inf.readInt(1, 10, "value");
            if (i + 1 < N) {
                inf.readSpace();   // exactly one space between numbers
            } else {
                inf.readEoln();    // end of this line after the last number
            }
        }
    }

    inf.readEof();
    return 0;
}
