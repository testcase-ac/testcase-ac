#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 700, "N");
    inf.readSpace();
    int m = inf.readInt(2, 700, "M");
    inf.readSpace();
    int k = inf.readInt(0, 1400, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }

            int value = inf.readInt(0, 1000000000, "F_ij");
            if (i == 1 && j == 1) {
                ensuref(value == 0, "F_11 must be 0, found %d", value);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
