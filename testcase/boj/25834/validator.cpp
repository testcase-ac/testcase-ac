#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();
    inf.readEof();
}
