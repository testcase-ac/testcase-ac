#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int l = inf.readInt(1, 1000, "L");
        inf.readEoln();

        inf.readInts(l, -10000, 10000, "value");
        inf.readEoln();
    }

    inf.readEof();
}
