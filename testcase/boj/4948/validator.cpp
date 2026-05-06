#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 123456;
    const int MAX_T = 100000;

    int test_count = 0;
    while (true) {
        // Read n: allow 0 for the terminator, otherwise 1 ≤ n ≤ MAX_N
        int n = inf.readInt(0, MAX_N, "n");
        inf.readEoln();

        if (n == 0) {
            // Terminator reached
            break;
        }

        // Now this is a real test case
        test_count++;
        ensuref(n >= 1,
                "n must be at least 1 for test #%d, but got %d",
                test_count, n);
        // Upper bound already enforced by readInt

        ensuref(test_count <= MAX_T,
                "Number of test cases exceeds limit: %d > %d",
                test_count, MAX_T);
    }

    inf.readEof();
    return 0;
}
