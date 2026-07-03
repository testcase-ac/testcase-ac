#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int w = inf.readInt(1, 100000, "W");
        inf.readSpace();
        int n = inf.readInt(2, 1000000000, "N");
        inf.readEoln();

        for (int i = 1; i <= w; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            inf.readInt(1, n, "X_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
