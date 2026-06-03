#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(0LL, 1000000000000LL, "N");
    inf.readEoln();
    inf.readEof();
}
