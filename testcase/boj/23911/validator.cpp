#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500000, "N");
        inf.readSpace();
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readEoln();

        if (n > 100) {
            ++largeCases;
        }
        ensuref(largeCases <= 5, "more than 5 cases have N > 100");

        for (int i = 2; i <= n; ++i) {
            if (i > 2) {
                inf.readSpace();
            }
            inf.readInt(1, i - 1, "parent_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
