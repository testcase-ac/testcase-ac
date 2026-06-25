#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 150000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000000, "X_i");
        inf.readSpace();
        inf.readInt(1, 100000000, "Y_i");
        inf.readSpace();
        inf.readInt(1, 100000000, "Z_i");
        inf.readEoln();
    }

    inf.readEof();
}
