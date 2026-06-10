#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 10000000000000000LL, "x_0");
    inf.readSpace();
    inf.readInt(1, 50, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
