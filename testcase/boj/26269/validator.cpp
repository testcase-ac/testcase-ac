#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 100000, "K");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "X");
    inf.readEoln();
    inf.readEof();
}
