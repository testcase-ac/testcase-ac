#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000000000LL, "h");
    inf.readEoln();

    inf.readInt(1, 100000, "a");
    inf.readSpace();
    inf.readInt(1, 100000, "b");
    inf.readSpace();
    inf.readInt(1, 100000, "c");
    inf.readEoln();

    inf.readEof();
}
