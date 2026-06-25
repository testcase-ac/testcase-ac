#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 5000, "N");
        inf.readEoln();

        inf.readInts(n, 1, 100000, "a");
        inf.readEoln();
    }

    inf.readEof();
}
