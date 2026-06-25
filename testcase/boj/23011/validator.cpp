#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(-1000000000LL, 1000000000LL, "G_0_0");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "G_0_1");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "G_0_2");
        inf.readEoln();

        inf.readLong(-1000000000LL, 1000000000LL, "G_1_0");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "G_1_2");
        inf.readEoln();

        inf.readLong(-1000000000LL, 1000000000LL, "G_2_0");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "G_2_1");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "G_2_2");
        inf.readEoln();
    }

    inf.readEof();
}
