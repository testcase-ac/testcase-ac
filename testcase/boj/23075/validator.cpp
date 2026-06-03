#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 10000000000LL, "n");
    inf.readEoln();
    inf.readEof();
}
