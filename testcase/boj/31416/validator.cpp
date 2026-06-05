#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 1000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        inf.readInt(1, 100, "T_A");
        inf.readSpace();
        inf.readInt(1, 100, "T_B");
        inf.readSpace();
        inf.readInt(1, 100, "V_A");
        inf.readSpace();
        inf.readInt(1, 100, "V_B");
        inf.readEoln();
    }

    inf.readEof();
}
