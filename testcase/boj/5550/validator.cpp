#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000, "C_i");
        inf.readSpace();
        inf.readInt(1, 10, "G_i");
        inf.readEoln();
    }

    inf.readEof();
}
