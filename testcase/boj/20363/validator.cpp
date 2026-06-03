#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(0LL, 1000000000LL, "X");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "Y");
    inf.readEoln();
    inf.readEof();
}
