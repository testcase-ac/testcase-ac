#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(2LL, 1000000000000LL, "S");
    inf.readSpace();
    inf.readLong(2LL, 1000000000000LL, "X");
    inf.readEoln();
    inf.readEof();
}
