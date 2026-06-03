#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(1, 50000, "H");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 5000, "P_i");
        inf.readSpace();
        inf.readInt(1, 5000, "C_i");
        inf.readEoln();
    }

    inf.readEof();
}
