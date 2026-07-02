#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 1000, "M");
        inf.readSpace();
        inf.readInt(1, 10000, "B");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            inf.readInt(1, 20000, "p_i");
            inf.readSpace();
            inf.readInt(1, 200000, "q_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
