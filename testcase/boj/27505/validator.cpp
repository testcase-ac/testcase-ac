#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(5LL, 100000000000000LL, "N");
    inf.readSpace();
    inf.readInt(2, 10000000, "A");
    inf.readSpace();
    inf.readInt(2, 10000000, "B");
    inf.readEoln();
    inf.readEof();
}
