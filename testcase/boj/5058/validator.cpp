#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 20000, "m");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            inf.readInt(1, 10000, "w_i");
            inf.readSpace();
            inf.readInt(1, 10000, "h_i");
            if (i == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
