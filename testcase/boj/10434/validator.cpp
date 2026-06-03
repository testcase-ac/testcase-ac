#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        setTestCase(i);

        // CHECK: K is described only as the data set number, with no explicit upper bound.
        inf.readInt(1, 1000000000, "K");
        inf.readSpace();
        inf.readInt(1, 10000, "m");
        inf.readEoln();
    }

    inf.readEof();
}
