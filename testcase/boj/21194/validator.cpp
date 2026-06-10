#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 10000, "g_i");
        inf.readEoln();
    }

    inf.readEof();
}
