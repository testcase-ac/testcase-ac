#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(0, 10000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 100000, "a_i");
        inf.readSpace();
        inf.readInt(0, 100000, "b_i");
        inf.readSpace();
        inf.readInt(0, 10000, "c_i");
        inf.readEoln();
    }

    inf.readEof();
}
