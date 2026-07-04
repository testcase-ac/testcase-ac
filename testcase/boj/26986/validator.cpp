#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 500, "C");
    inf.readSpace();
    int n = inf.readInt(c, 500, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, "X_i");
        inf.readSpace();
        inf.readInt(1, 10000, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
