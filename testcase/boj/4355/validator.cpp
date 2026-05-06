#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect a sequence of n values, each on its own line,
    // 1 <= n <= 1e9, terminated by a line with n = 0.
    // Number of test cases (excluding the terminating 0) <= 100000.

    int tc = 0;
    while (true) {
        // Read n, allowing 0 for the sentinel
        long long n = inf.readLong(0LL, 1000000000LL, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }
        // For non-sentinel values, n must be at least 1
        ensuref(n >= 1, "n must be positive before the terminating 0, found %lld", n);

        tc++;
    }

    ensuref(tc <= 100000, "Number of test cases %d exceeds 100000", tc);

    inf.readEof();
    return 0;
}
