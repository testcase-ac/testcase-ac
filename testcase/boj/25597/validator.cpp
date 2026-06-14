#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "X");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "T");
    inf.readEoln();
    inf.readEof();
}
