#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(0LL, 1000000000000LL, "x");
    inf.readSpace();
    inf.readLong(0LL, 1000000000000LL, "y");
    inf.readEoln();
    inf.readEof();
}
