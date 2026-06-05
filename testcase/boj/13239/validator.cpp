#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        inf.readInt(0, n, "k");
        inf.readEoln();
    }

    inf.readEof();
}
