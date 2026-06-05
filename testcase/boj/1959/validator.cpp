#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(2LL, 2100000000LL, "M");
    inf.readSpace();
    inf.readLong(2LL, 2100000000LL, "N");
    inf.readEoln();
    inf.readEof();
}
