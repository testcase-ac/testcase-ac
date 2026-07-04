#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "k");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int p = inf.readInt(1, n, "p");
        inf.readSpace();
        int t = inf.readInt(1, n - p + 1, "t");
        inf.readEoln();
    }

    inf.readEof();
}
