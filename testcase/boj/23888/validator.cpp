#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "a");
    inf.readSpace();
    inf.readInt(0, 1000000, "d");
    inf.readEoln();

    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int l = inf.readInt(1, 1000000, "l");
        inf.readSpace();
        int r = inf.readInt(l, 1000000, "r");
        inf.readEoln();
    }

    inf.readEof();
}
