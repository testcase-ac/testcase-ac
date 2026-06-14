#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(0, 1000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000000, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
