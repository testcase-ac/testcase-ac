#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 10000000, "w");
        inf.readEoln();
    }

    inf.readInt(1, n, "start");
    inf.readSpace();
    inf.readInt(1, n, "end");
    inf.readEoln();
    inf.readEof();

    return 0;
}
