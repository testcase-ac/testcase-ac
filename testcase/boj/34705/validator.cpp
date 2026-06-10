#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long x = inf.readLong(1LL, 1000000000LL, "X");
        inf.readSpace();
        long long y = inf.readLong(x, 1000000000LL, "Y");
        inf.readEoln();

        for (int i = 1; i <= 5; ++i) {
            inf.readInt(1, 100000000, "a_i");
            if (i < 5) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
