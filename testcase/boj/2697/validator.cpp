#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        inf.readToken("[1-9][0-9]{0,79}", "A");
        inf.readEoln();
    }

    inf.readEof();
}
