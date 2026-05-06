#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXV = 10000;
    const int MAXT = 100000;
    int testCount = 0;
    while (true) {
        // Read two integers, allow 0..MAXV to catch the terminator
        int a = inf.readInt(0, MAXV, "a");
        inf.readSpace();
        int b = inf.readInt(0, MAXV, "b");
        inf.readEoln();

        // Either both are zero (termination) or both are non-zero
        if (a == 0 || b == 0) {
            ensuref(a == 0 && b == 0,
                    "Invalid zero usage: one of (a,b) is zero but not both (%d, %d)", a, b);
            break;  // termination line
        }

        // Now (a,b) is a real test case
        ++testCount;
        ensuref(testCount <= MAXT,
                "Too many test cases: %d (max %d)", testCount, MAXT);

        // Both must be natural numbers 1..MAXV
        ensuref(a >= 1 && a <= MAXV,
                "Value a out of range: %d (allowed 1..%d)", a, MAXV);
        ensuref(b >= 1 && b <= MAXV,
                "Value b out of range: %d (allowed 1..%d)", b, MAXV);

        // They must not be equal
        ensuref(a != b,
                "Numbers must not be equal: %d %d", a, b);
    }

    inf.readEof();
    return 0;
}
