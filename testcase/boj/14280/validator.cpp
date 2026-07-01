#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "a");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "b");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "c");
    inf.readEoln();
    inf.readEof();
}
