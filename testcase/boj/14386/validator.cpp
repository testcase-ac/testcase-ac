#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(32, 32, "N");
        inf.readSpace();
        int j = inf.readInt(500, 500, "J");
        inf.readEoln();
    }

    inf.readEof();
}
