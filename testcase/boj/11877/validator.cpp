#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000LL, "X");
    inf.readEoln();
    inf.readEof();
}
