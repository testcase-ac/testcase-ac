#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readEoln();
        inf.readInt(2, 1000000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
