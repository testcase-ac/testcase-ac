#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 100, "M");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            inf.readInt(0, 1000, "P1");
            inf.readSpace();
            inf.readInt(0, 1000, "P2");
            inf.readEoln();
        }
    }

    inf.readEof();
}
