#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 99999999LL, "A");
    inf.readSpace();
    inf.readLong(1LL, 99999999LL, "B");
    inf.readEoln();
    inf.readEof();
}
