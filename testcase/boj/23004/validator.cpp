#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 300000, "N");
        inf.readEoln();

        if (n > 2000) {
            ++largeCases;
        }

        inf.readLong(0LL, 1000000000LL, "A_i");
        for (int i = 2; i <= n; ++i) {
            inf.readSpace();
            inf.readLong(0LL, 1000000000LL, "A_i");
        }
        inf.readEoln();
    }

    ensuref(largeCases <= 10, "at most 10 test cases may have N > 2000");

    inf.readEof();
}
