#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(2, 20, "N");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(3, 9999, "M");
        inf.readSpace();
        inf.readInt(0, 1, "V");
        inf.readEoln();

        ensuref(m % 2 == 1, "M must be odd, got %d", m);

        int internalNodes = (m - 1) / 2;
        int leafNodes = (m + 1) / 2;

        for (int i = 1; i <= internalNodes; ++i) {
            inf.readInt(0, 1, "G");
            inf.readSpace();
            inf.readInt(0, 1, "C");
            inf.readEoln();
        }

        for (int i = 1; i <= leafNodes; ++i) {
            inf.readInt(0, 1, "I");
            inf.readEoln();
        }
    }

    inf.readEof();
}
