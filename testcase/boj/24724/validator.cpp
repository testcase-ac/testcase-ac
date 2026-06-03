#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10000, "N");
        inf.readEoln();

        long long a = inf.readLong(1LL, 1000000000LL, "A");
        inf.readSpace();
        long long b = inf.readLong(1LL, 1000000000LL, "B");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readLong(1LL, a, "u_i");
            inf.readSpace();
            inf.readLong(1LL, b, "v_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
