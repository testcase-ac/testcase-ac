#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int a = inf.readInt(1, 10000000, "a");
        inf.readSpace();
        int b = inf.readInt(a, 10000000, "b");
        inf.readSpace();
        int c = inf.readInt(1, 10000000, "c");
        inf.readSpace();
        inf.readInt(c, 10000000, "d");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
