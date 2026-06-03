#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "x");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "y");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "z");
    inf.readEoln();
    inf.readEof();
}
