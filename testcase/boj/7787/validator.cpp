#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "r");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "g");
    inf.readEoln();
    inf.readEof();
}
