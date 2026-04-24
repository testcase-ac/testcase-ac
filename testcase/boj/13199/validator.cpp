#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 20000, "T");
    inf.readEoln();

    // For each test case, read P, M, F, C with appropriate checks
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // P: chicken price
        int P = inf.readInt(1, 50000, "P");
        inf.readSpace();

        // M: money available
        int M = inf.readInt(1, 1000000, "M");
        inf.readSpace();

        // F: coupons needed for a free chicken
        int F = inf.readInt(2, 1000, "F");
        inf.readSpace();

        // C: coupons given per purchase
        int C = inf.readInt(1, 1000, "C");
        // Check the implied constraint C < F
        ensuref(C < F,
                "On test case %d, C (%d) must be strictly less than F (%d)",
                tc, C, F);

        inf.readEoln();
    }

    // No extra content after the test cases
    inf.readEof();
    return 0;
}
