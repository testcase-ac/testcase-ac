#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(1, 300, "R");
        inf.readSpace();
        int c = inf.readInt(1, 300, "C");
        inf.readEoln();

        for (int i = 0; i < r; ++i) {
            inf.readInts(c, 0, 2000000, "G_i_j");
            inf.readEoln();
        }
    }

    inf.readEof();
}
