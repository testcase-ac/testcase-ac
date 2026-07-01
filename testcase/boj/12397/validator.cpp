#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            int a = inf.readInt(0, 2001, "a_i");
            inf.readSpace();
            int b = inf.readInt(a, 2001, "b_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
