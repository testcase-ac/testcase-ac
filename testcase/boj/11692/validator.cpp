#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000LL, "m");
    inf.readEoln();
    inf.readEof();
}
