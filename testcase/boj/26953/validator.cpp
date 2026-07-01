#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 200000, "M");
    inf.readSpace();
    inf.readLong(0LL, 1000000000000LL, "b");
    inf.readEoln();
    inf.readEof();
}
