#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_N = 100000;
    const int MAX_Q = 100000;
    const int MIN_A = -100000;
    const int MAX_A = 100000;

    int testCnt = 0;
    while (true) {
        // Read n, allow 0 as sentinel
        int n = inf.readInt(0, MAX_N, "n");
        if (n == 0) {
            // sentinel line must be just "0\n"
            inf.readEoln();
            break;
        }
        // Non-sentinel: read q on same line
        inf.readSpace();
        int q = inf.readInt(1, MAX_Q, "q");
        inf.readEoln();

        // Count test cases
        testCnt++;
        ensuref(testCnt <= MAX_T,
                "Number of test cases exceeds limit: %d > %d", testCnt, MAX_T);

        // Read array a[1..n]
        vector<int> a = inf.readInts(n, MIN_A, MAX_A, "a_i");
        inf.readEoln();
        // Check non-decreasing
        for (int i = 0; i + 1 < n; i++) {
            ensuref(a[i] <= a[i+1],
                    "Array not non-decreasing at position %d: %d > %d",
                    i+1, a[i], a[i+1]);
        }

        // Read q queries
        for (int qi = 0; qi < q; qi++) {
            int l = inf.readInt(1, n, "l_i");
            inf.readSpace();
            int r = inf.readInt(1, n, "r_i");
            inf.readEoln();
            ensuref(l <= r,
                    "Query indices invalid at query %d: l=%d > r=%d", qi+1, l, r);
        }
    }

    inf.readEof();
    return 0;
}
