#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, i - 1, "X_i");
        inf.readSpace();
        inf.readInt(0, x + 1, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
