#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1000, "q");
    inf.readSpace();
    inf.readInt(-5, 5, "u");
    inf.readSpace();
    inf.readInt(-5, 5, "v");
    inf.readEoln();

    inf.readInts(n, -100, 100, "k");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int c = inf.readInt(0, 1, "c");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        if (c == 0) {
            inf.readInt(a, n, "b");
        } else {
            inf.readInt(-100, 100, "b");
        }
        inf.readEoln();
    }

    inf.readEof();
}
