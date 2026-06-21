#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    inf.readInt(1, 5, "M");
    inf.readEoln();

    inf.readEof();
}
