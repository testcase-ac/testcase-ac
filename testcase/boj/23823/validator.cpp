#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int t = inf.readInt(1, 2, "t");
        inf.readSpace();
        inf.readInt(1, n, "a");
        inf.readEoln();
    }

    inf.readEof();
}
