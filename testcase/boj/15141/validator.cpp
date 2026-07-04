#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "h");
    inf.readSpace();
    inf.readInt(1, 100, "w");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "n");
    inf.readEoln();
    inf.readEof();
}
