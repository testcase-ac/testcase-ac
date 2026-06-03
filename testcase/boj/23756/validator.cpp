#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    inf.readInt(0, 359, "a_0");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 359, format("a_%d", i));
        inf.readEoln();
    }

    inf.readEof();
}
