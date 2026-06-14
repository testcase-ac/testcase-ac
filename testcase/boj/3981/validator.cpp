#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500, "n");
        for (int i = 1; i <= n; ++i) {
            inf.readSpace();
            inf.readInt(0, 50000000, "x_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
