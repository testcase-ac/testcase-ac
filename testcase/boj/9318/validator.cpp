#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read number of rectangles
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        for (int i = 0; i < n; i++) {
            // Read one rectangle: x1, y1, x2, y2
            long long x1 = inf.readLong(0LL, 1000000LL, "x1");
            inf.readSpace();
            long long y1 = inf.readLong(0LL, 1000000LL, "y1");
            inf.readSpace();
            long long x2 = inf.readLong(0LL, 1000000LL, "x2");
            inf.readSpace();
            long long y2 = inf.readLong(0LL, 1000000LL, "y2");
            inf.readEoln();

            // Ensure rectangle is non-degenerate and well-formed
            ensuref(x1 < x2, "Test case %d, rectangle %d: x1 >= x2 (%lld >= %lld)", 
                    tc, i + 1, x1, x2);
            ensuref(y1 < y2, "Test case %d, rectangle %d: y1 >= y2 (%lld >= %lld)", 
                    tc, i + 1, y1, y2);
        }
    }

    inf.readEof();
    return 0;
}
