#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        for (int digit = 1; digit <= 9; ++digit) {
            int count = inf.readInt(0, 9, "P_i");
            // CHECK: The input format lists counts for digits 1..9, but the
            // problem prose defines the available digits as even digits and
            // all statement samples have zero counts for odd digits.
            if (digit % 2 == 1) {
                ensuref(count == 0,
                        "odd digit %d has count %d in testcase %d",
                        digit, count, tc);
            }

            if (digit == 9) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
