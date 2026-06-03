#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-100000000, 100000000, "a_i");
        inf.readSpace();
        inf.readInt(-100000000, 100000000, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
