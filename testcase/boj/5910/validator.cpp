#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 25000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 50000, "u_i");
        inf.readSpace();
        inf.readInt(1, 50000, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
