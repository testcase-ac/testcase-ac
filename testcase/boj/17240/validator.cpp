#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 20000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1000, "a_i");
        inf.readSpace();
        inf.readInt(0, 1000, "b_i");
        inf.readSpace();
        inf.readInt(0, 1000, "c_i");
        inf.readSpace();
        inf.readInt(0, 1000, "d_i");
        inf.readSpace();
        inf.readInt(0, 1000, "e_i");
        inf.readEoln();
    }

    inf.readEof();
}
