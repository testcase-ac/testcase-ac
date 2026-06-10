#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 1000000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
