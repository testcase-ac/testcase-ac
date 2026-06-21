#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000000LL, "N");
    inf.readSpace();
    inf.readInt(1, 50, "K");
    inf.readEoln();
    inf.readEof();
}
