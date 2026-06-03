#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 100, "P");
    inf.readEoln();

    for (int tc = 1; tc <= p; ++tc) {
        setTestCase(tc);

        // CHECK: K has no stated bound; treat it as a nonnegative dataset identifier.
        int k = inf.readInt(0, 1000000000, "K");
        inf.readSpace();
        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            if (i % 10 != 0) {
                inf.readSpace();
            }

            // CHECK: Korean says values are less than 10^9, but the English original says no larger than 10^9.
            inf.readInt(1, 1000000000, "a_i");

            if (i % 10 == 9 || i == n - 1) {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
