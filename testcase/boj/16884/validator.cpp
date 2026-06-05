#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        inf.readInt(1, 10000, "N");
        inf.readEoln();
    }

    inf.readEof();
}
