#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 400, "N");
        inf.readSpace();
        int d = inf.readInt(2, 1000000000, "D");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            inf.readInt(0, d - 1, "V_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
