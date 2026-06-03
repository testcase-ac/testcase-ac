#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(2LL, 1000000000LL, "R");
    inf.readEoln();
    inf.readEof();
}
