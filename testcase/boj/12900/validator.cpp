#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int M = inf.readInt(1, 10000, "M");
        inf.readSpace();
        inf.readInt(0, 1, "V");
        inf.readEoln();

        ensuref(M % 2 == 1, "M must be odd, found %d", M);

        int internalNodes = (M - 1) / 2;
        int leafNodes = (M + 1) / 2;

        for (int i = 1; i <= internalNodes; ++i) {
            inf.readInt(0, 1, "a_i");
            inf.readSpace();
            inf.readInt(0, 1, "b_i");
            inf.readEoln();
        }

        for (int i = 1; i <= leafNodes; ++i) {
            inf.readInt(0, 1, "a_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
