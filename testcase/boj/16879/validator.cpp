#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 2999, "x");
        inf.readSpace();
        int y = inf.readInt(0, 2999, "y");
        inf.readEoln();
    }

    inf.readEof();
}
