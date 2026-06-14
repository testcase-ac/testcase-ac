#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        inf.readInts(n, -100, 100, "s_i");
        inf.readEoln();
    }

    inf.readEof();
}
