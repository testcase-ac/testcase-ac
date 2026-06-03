#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        for (int printer = 1; printer <= 3; ++printer) {
            inf.readInt(0, 1000000, "C_i");
            inf.readSpace();
            inf.readInt(0, 1000000, "M_i");
            inf.readSpace();
            inf.readInt(0, 1000000, "Y_i");
            inf.readSpace();
            inf.readInt(0, 1000000, "K_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
