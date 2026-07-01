#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 1000, "T");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();
    inf.readEof();
}
