#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readUnsignedLong(1ULL, 4294967295ULL, "n");
    inf.readSpace();
    inf.readUnsignedLong(1ULL, 18446744073709551614ULL, "a");
    inf.readEoln();
    inf.readEof();

    return 0;
}
