#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
        inf.readEoln();

        long long s = inf.readLong(1LL, 1000000000LL, "s");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t");
        inf.readEoln();
    }

    inf.readEof();
}
