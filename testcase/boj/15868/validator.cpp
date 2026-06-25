#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 10000000000000LL, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
