#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 100, "M");
        inf.readEoln();

        long long totalStock = 0;
        for (int i = 1; i <= m; ++i) {
            int s = inf.readInt(0, 10000, "s_i");
            inf.readSpace();
            inf.readInt(0, 10000, "p_i");
            inf.readSpace();
            inf.readInt(0, 1000000, "o_i");
            inf.readEoln();

            totalStock += s;
        }

        ensuref(n <= totalStock, "case %d has N=%d but total stock is %lld", tc, n, totalStock);
    }

    inf.readEof();
}
