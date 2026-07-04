#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int p = inf.readInt(1, 1000000000, "p");
    inf.readSpace();
    inf.readInt(1, 1000000000, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, p, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
