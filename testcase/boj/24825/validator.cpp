#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 100000, "h");
    inf.readSpace();
    int c = inf.readInt(1, 100000, "c");
    inf.readEoln();

    for (int i = 0; i < c; ++i) {
        inf.readLong(1LL, 1000000000LL, "a");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "d");
        inf.readEoln();
    }

    inf.readEof();
}
