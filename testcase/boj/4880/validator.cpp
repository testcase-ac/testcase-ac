#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCnt = 0;
    while (true) {
        // Read three integers a1, a2, a3 with strict spacing and newline
        int a1 = inf.readInt(-9999, 9999, "a1");
        inf.readSpace();
        int a2 = inf.readInt(-9999, 9999, "a2");
        inf.readSpace();
        int a3 = inf.readInt(-9999, 9999, "a3");
        inf.readEoln();

        // Termination condition: exactly "0 0 0"
        if (a1 == 0 && a2 == 0 && a3 == 0)
            break;

        // Count test cases and enforce upper bound 100000
        caseCnt++;
        ensuref(caseCnt <= 100000,
                "Number of test cases exceeds limit (100000): %d", caseCnt);

        // Ensure all three are pairwise distinct
        ensuref(a1 != a2,
                "Test case %d: a1 and a2 must be distinct, got %d and %d",
                caseCnt, a1, a2);
        ensuref(a1 != a3,
                "Test case %d: a1 and a3 must be distinct, got %d and %d",
                caseCnt, a1, a3);
        ensuref(a2 != a3,
                "Test case %d: a2 and a3 must be distinct, got %d and %d",
                caseCnt, a2, a3);

        // Check if it's a valid non-constant AP
        int d1 = a2 - a1;
        int d2 = a3 - a2;
        bool isAP = (d1 != 0) && (d1 == d2);

        // Check if it's a valid non-constant GP with integer ratio
        bool isGP = false;
        if (a1 != 0 && a2 != 0) {
            if (a2 % a1 == 0 && a3 % a2 == 0) {
                int r1 = a2 / a1;
                int r2 = a3 / a2;
                if (r1 != 0 && r1 == r2)
                    isGP = true;
            }
        }

        // Must be exactly one of AP or GP (but not both non-degenerately)
        ensuref(isAP || isGP,
                "Test case %d: Sequence (%d, %d, %d) is neither valid AP nor valid GP",
                caseCnt, a1, a2, a3);
    }

    inf.readEof();
    return 0;
}
