#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "S");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "F");
    inf.readSpace();
    inf.readInt(1, 100000, "M");
    inf.readEoln();
    inf.readEof();
}
