#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(2LL, 1000000000000000LL, "N");
    inf.readSpace();
    inf.readInt(0, 50, "k");
    inf.readEoln();
    inf.readEof();
}
