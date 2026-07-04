#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int d = inf.readInt(1, 1000, "d");
        inf.readSpace();
        inf.readInt(1, 10, "x");
        inf.readSpace();
        inf.readInt(1, 10, "s");
        inf.readEoln();

        for (int day = 1; day <= d; ++day) {
            inf.readInt(1, 1000, "c");
            inf.readSpace();
            inf.readInt(1, 50, "p_l");
            inf.readSpace();
            inf.readInt(1, 500, "p_s");
            inf.readEoln();
        }
    }

    inf.readEof();
}
