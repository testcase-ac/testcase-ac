#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(4LL, 1000000000000000000LL, "n");
    inf.readSpace();
    inf.readInt(1, 1000000000, "f1");
    inf.readSpace();
    inf.readInt(1, 1000000000, "f2");
    inf.readSpace();
    inf.readInt(1, 1000000000, "f3");
    inf.readSpace();
    inf.readInt(1, 1000000000, "c");
    inf.readEoln();
    inf.readEof();
}
