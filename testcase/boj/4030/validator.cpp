#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int tc = 0;
    while (true) {
        // Read a and b (both in [0, 1e9]), two integers separated by exactly one space, then newline
        int a = inf.readInt(0, 1000000000, "a");
        inf.readSpace();
        int b = inf.readInt(0, 1000000000, "b");
        inf.readEoln();

        // Termination condition
        if (a == 0 && b == 0) {
            break;
        }

        // Normal test case validations
        tc++;
        ensuref(tc <= MAX_CASES,
                "Number of test cases exceeds the limit: %d > %d", tc, MAX_CASES);
        ensuref(a > 0,
                "Constraint violation: a must be > 0 for test case %d, but got a = %d", tc, a);
        ensuref(a < b,
                "Constraint violation: a < b must hold for test case %d, but got a = %d, b = %d", tc, a, b);
        // b <= 1e9 is already ensured by readInt's upper bound
    }

    inf.readEof();
    return 0;
}
