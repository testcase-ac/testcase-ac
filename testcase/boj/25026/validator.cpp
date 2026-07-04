#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 1000000000, "s_i");
        inf.readSpace();
        inf.readInt(0, 1000000000, "e_i");
        inf.readEoln();
    }

    inf.readEof();
}
