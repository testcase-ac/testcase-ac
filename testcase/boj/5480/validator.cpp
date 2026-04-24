#include "testlib.h"
#include <cassert>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read grid size n, number of ships k, number of shots l
        long long n = inf.readLong(1LL, 1000000000LL, "n");
        inf.readSpace();
        int k = inf.readInt(1, 100000, "k");
        inf.readSpace();
        int l = inf.readInt(1, 100000, "l");
        inf.readEoln();

        // Read the k ships
        for (int i = 0; i < k; i++) {
            long long x1 = inf.readLong(1LL, n, "x_i");
            inf.readSpace();
            long long y1 = inf.readLong(1LL, n, "y_i");
            inf.readSpace();
            long long x2 = inf.readLong(1LL, n, "x'_i");
            inf.readSpace();
            long long y2 = inf.readLong(1LL, n, "y'_i");
            inf.readSpace();
            int w = inf.readInt(1, 1000000, "w_i");
            inf.readEoln();

            // Each ship must have positive length (not a point)
            ensuref(x1 != x2 || y1 != y2,
                    "Ship %d is degenerate (endpoints are identical): (%lld,%lld) and (%lld,%lld)",
                    i+1, x1, y1, x2, y2);
        }

        // Read the l shots
        for (int i = 0; i < l; i++) {
            long long a = inf.readLong(1LL, n, "a_i");
            inf.readSpace();
            int b = inf.readInt(0, 1, "b_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
