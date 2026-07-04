#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(0, (1 << 30) - 1, "L");
    inf.readEoln();

    inf.readInt(1, n, "S");
    inf.readSpace();
    inf.readInt(1, n, "T");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, n, "B");
        inf.readSpace();
        inf.readInt(1, n, "C");
        inf.readSpace();
        inf.readInt(1, n, "D");
        inf.readEoln();
    }

    inf.readEof();
}
