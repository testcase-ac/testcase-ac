#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        long long X = inf.readLong(0LL, 1000000000LL, "X");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000000LL, "y");
        inf.readSpace();
        long long Z = inf.readLong(0LL, 1000000000LL, "Z");
        inf.readEoln();

        (void)X;
        (void)y;
        (void)Z;

        inf.readInts(n, -1000000, 1000000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
}
