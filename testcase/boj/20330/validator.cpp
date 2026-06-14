#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 999999999999999999LL, "n");
    inf.readEoln();
    inf.readEof();
}
