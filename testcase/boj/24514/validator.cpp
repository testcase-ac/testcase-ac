#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 99, "T");
    inf.readSpace();
    inf.readInt(2, 9, "K");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        inf.readInt(1, 1999999999, "N");
        inf.readEoln();
    }

    inf.readEof();
}
