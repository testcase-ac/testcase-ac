#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readSpace();
        inf.readInt(1, 100000, "B");
        inf.readEoln();

        inf.readInts(n, 1, 1000, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
