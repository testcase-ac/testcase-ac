#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We allow up to 100,000 test cases (excluding the terminating 0).
    int tc = 0;
    while (true) {
        // Read N for this test case. N must be between 0 and 100 inclusive.
        int N = inf.readInt(0, 100, "N");
        // Each N must occupy exactly one line.
        inf.readEoln();

        // The input ends with a line "0".
        if (N == 0) {
            break;
        }
        // Count only the real test cases (N > 0).
        tc++;
        ensuref(tc <= 100000,
                "Number of test cases exceeds limit: %d (max 100000)", tc);
    }

    // No extra characters after the terminating line.
    inf.readEof();
    return 0;
}
