#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000, "X");
        inf.readSpace();
        inf.readInt(1, 1000000, "Y");
        inf.readSpace();
        inf.readInt(1, 1000000, "R");
        inf.readEoln();
    }

    inf.readEof();
}
