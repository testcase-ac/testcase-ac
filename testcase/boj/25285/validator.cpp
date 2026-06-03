#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 200, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 200, "height");
        inf.readSpace();
        inf.readInt(1, 200, "weight");
        inf.readEoln();
    }

    inf.readEof();
}
