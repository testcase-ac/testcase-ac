#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 200, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50, "n");
        inf.readEoln();

        inf.readLongs(n, 0LL, 10000000000000000LL, "f_i");
        inf.readEoln();
    }

    inf.readEof();
}
