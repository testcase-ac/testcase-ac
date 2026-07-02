#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "m");
    inf.readEoln();
    inf.readEof();
}
