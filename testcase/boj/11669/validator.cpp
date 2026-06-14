#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "r");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "p");
    inf.readEoln();
    inf.readEof();
}
