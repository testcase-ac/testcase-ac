#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        inf.readInt(1, 100000, "K");
        inf.readEoln();
    }

    inf.readEof();
}
