#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 100, "S_i");
            inf.readSpace();
            inf.readInt(1, 100000, "E_i");
            inf.readSpace();
            inf.readInt(0, 100000, "L_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
