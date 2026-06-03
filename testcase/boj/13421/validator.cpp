#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 4; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();
    }

    inf.readEof();
}
