#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200, "n");
        inf.readEoln();

        inf.readInts(n, 1, 100000, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
