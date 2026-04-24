#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read four integers a, b, c, d with bounds -5000 ≤ a,b,c,d ≤ 2000
        int a = inf.readInt(-5000, 2000, "a");
        inf.readSpace();
        int b = inf.readInt(-5000, 2000, "b");
        inf.readSpace();
        int c = inf.readInt(-5000, 2000, "c");
        inf.readSpace();
        int d = inf.readInt(-5000, 2000, "d");
        inf.readEoln();

        // Validate ordering constraints: a ≤ b ≤ c ≤ d
        ensuref(a <= b, "Constraint violated: a > b (%d > %d)", a, b);
        ensuref(b <= c, "Constraint violated: b > c (%d > %d)", b, c);
        ensuref(c <= d, "Constraint violated: c > d (%d > %d)", c, d);

        // Check for sentinel: end of input
        if (a == 0 && b == 0 && c == 0 && d == 0) {
            break;
        }

        // Count this as a real test case
        tc++;
        // Since problem statement does not specify an explicit limit on test cases,
        // enforce a reasonable upper bound of 100000
        ensuref(tc <= 100000, "Number of test cases exceeds limit: %d > %d", tc, 100000);
    }

    // No extra characters or lines after the sentinel line
    inf.readEof();
    return 0;
}
