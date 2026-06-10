#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; cap it to keep input size practical.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 1000000000, "K");
        inf.readSpace();
        inf.readInt(1, 1000, "M");
        inf.readEoln();
    }

    inf.readEof();
}
