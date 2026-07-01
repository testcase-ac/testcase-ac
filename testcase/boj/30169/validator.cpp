#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 1000000000, "x");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readEoln();
    inf.readEof();
}
