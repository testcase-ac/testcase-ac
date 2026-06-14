#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(0, n, "A_i");
        inf.readSpace();
        inf.readInt(0, n, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
