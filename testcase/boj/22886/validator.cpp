#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(-100, 100, "X");
        inf.readSpace();
        inf.readInt(-100, 100, "Y");
        inf.readSpace();
        inf.readToken("[CJ?]{1,1000}", "S");
        inf.readEoln();
    }

    inf.readEof();
}
