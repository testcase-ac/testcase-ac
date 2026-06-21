#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int minA = -268435456;
    const int maxA = 268435456;

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "n");
        inf.readEoln();

        inf.readInts(n, minA, maxA, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
