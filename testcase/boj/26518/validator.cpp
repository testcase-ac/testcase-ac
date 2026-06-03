#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "b");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "c");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "a1");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "a2");
    inf.readEoln();
    inf.readEof();
}
