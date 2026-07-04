#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readSpace();
        int m = inf.readInt(1, 100, "M");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readLong(1LL, 10000000000000000LL, "a_i");
            inf.readSpace();
            inf.readInt(1, 100, "A_i");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }

        for (int i = 1; i <= m; ++i) {
            inf.readLong(1LL, 10000000000000000LL, "b_i");
            inf.readSpace();
            inf.readInt(1, 100, "B_i");
            if (i == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
