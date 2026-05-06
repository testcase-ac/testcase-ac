#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long Q_MIN = 0LL;
    const long long Q_MAX = 100000000000000LL; // 1e14
    const int MAX_TESTS = 2000;

    int testCount = 0;
    while (true) {
        // Read q (allows 0 for terminator; canonical form enforced by readLong)
        long long q = inf.readLong(Q_MIN, Q_MAX, "q");
        testCount++;

        // Check number of test cases limit
        ensuref(testCount <= MAX_TESTS,
                "Number of lines (including terminating 0) exceeds %d", MAX_TESTS);

        // Each test case is on its own line
        inf.readEoln();

        if (q == 0) {
            // After the terminating 0 line, there must be EOF
            break;
        }

        // No additional global properties required by statement:
        //  - q must be positive when it's not the terminator; already ensured by range [0,1e14)
        ensuref(q > 0, "Non-terminating q must be positive, got %lld", q);
    }

    inf.readEof();
}
