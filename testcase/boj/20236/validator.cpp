#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readInt(1, 1000000000, "c");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000000, "a_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "b_i");
        inf.readSpace();
        inf.readInt(0, 1, "w_i");
        inf.readEoln();
    }

    inf.readEof();
}
