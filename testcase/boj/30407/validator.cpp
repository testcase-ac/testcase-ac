#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 18, "N");
    inf.readEoln();

    inf.readInt(1, 1000, "H");
    inf.readSpace();
    inf.readInt(1, 10, "D");
    inf.readSpace();
    inf.readInt(1, 3, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100, "R_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
