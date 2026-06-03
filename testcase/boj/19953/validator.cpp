#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "v0");
    inf.readSpace();
    inf.readInt(1, 1000, "m");
    inf.readSpace();
    inf.readInt(1, 1000000000, "t");
    inf.readEoln();
    inf.readEof();
}
