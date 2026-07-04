#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 16, "n");
        inf.readSpace();
        inf.readInt(1, 16, "c");
        inf.readSpace();
        inf.readInt(1, 1000, "m");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(0, 1000, "b");
            inf.readSpace();
            inf.readInt(0, 100, "p");
            inf.readEoln();
        }
    }

    inf.readEof();
}
