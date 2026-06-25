#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 2000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20000, "N");
        inf.readSpace();
        long long s = inf.readLong(0LL, 1000000000LL + n, "S");
        inf.readEoln();
    }

    inf.readEof();
}
