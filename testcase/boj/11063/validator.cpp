#include "testlib.h"
#include <vector>
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; tc++) {
        // Label errors with the current test case
        setTestCase(tc);

        // Read n and l
        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int l = inf.readInt(1, 100000000, "l");
        inf.readEoln();

        // Read and validate left endpoints
        long long prev = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            long long x = inf.readLong(-100000000LL, 100000000LL, "left_i");
            inf.readEoln();

            if (i > 0) {
                ensuref(x >= prev,
                        "Left endpoints not non-decreasing at index %d: %lld < %lld",
                        i + 1, x, prev);
            }
            prev = x;

            // Check right endpoint within allowed bounds: x + l <= 1e8
            __int128 r = (__int128)x + l;
            ensuref(r <= 100000000LL,
                    "Right endpoint out of bounds at index %d: %lld + %d = %lld > %d",
                    i + 1, x, l, (long long)r, 100000000LL);
        }

        // Read and validate the permutation (ordering of vertices)
        vector<char> seen(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int v = inf.readInt(1, n, "order_i");
            inf.readEoln();
            ensuref(!seen[v],
                    "Duplicate vertex in ordering at position %d: vertex %d",
                    i + 1, v);
            seen[v] = 1;
        }
        // Ensure it's a full permutation: no missing vertex
        for (int v = 1; v <= n; v++) {
            ensuref(seen[v],
                    "Missing vertex in ordering: %d",
                    v);
        }
    }

    inf.readEof();
    return 0;
}
