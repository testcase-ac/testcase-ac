#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_A = (1 << 20) - 1;
    constexpr int MAX_CASES = 100000;  // CHECK: statement gives no case count cap.

    int cases = 0;
    while (true) {
        int a = inf.readInt(0, MAX_A, "a");
        inf.readEoln();

        if (a == 0) break;
        ensuref(a >= 2, "a must be either the terminator 0 or at least 2, got %d", a);

        ++cases;
        ensuref(cases <= MAX_CASES, "too many test cases: %d", cases);
    }

    inf.readEof();
}
