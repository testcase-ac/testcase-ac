#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "a");
    inf.readSpace();
    inf.readInt(1, 1000000, "b");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "L");
    inf.readEoln();

    inf.readEof();
}
