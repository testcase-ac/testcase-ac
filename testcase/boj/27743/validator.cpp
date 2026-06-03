#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 3000000000LL, "N");
    inf.readSpace();
    inf.readLong(1LL, 3000000000LL, "M");
    inf.readEoln();
    inf.readEof();
}
