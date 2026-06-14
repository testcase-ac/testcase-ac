#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 1000000000, "F_i");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }

        for (int i = 1; i <= n; ++i) {
            inf.readInt(0, i - 1, "P_i");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
