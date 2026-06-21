#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 200000, "T_i");
        inf.readSpace();
        inf.readInt(0, 200000, "L_i");
        inf.readEoln();
    }

    inf.readEof();
}
