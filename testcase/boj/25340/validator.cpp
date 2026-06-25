#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = inf.readInt(1, 300000, "TC");
    inf.readEoln();

    long long totalN = 0;
    for (int t = 1; t <= tc; ++t) {
        setTestCase(t);

        int n = inf.readInt(1, 300000, "N");
        inf.readSpace();
        inf.readInt(1, 1000000000, "T");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 300000, "sum of N exceeds 300000 after test case %d", t);

        for (int i = 1; i <= n; ++i) {
            int a = inf.readInt(1, 1000, "A_i");
            inf.readSpace();
            int b = inf.readInt(1, 1000, "B_i");
            inf.readSpace();
            inf.readInt(0, 1000, "C_i");
            inf.readSpace();
            int d = inf.readInt(1, 1000, "D_i");
            inf.readEoln();

            ensuref(d <= b, "D_%d must be at most B_%d", i, i);
            ensuref(b < a, "B_%d must be less than A_%d", i, i);
        }

        for (int i = 0; i <= n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000, "E_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
