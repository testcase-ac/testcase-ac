#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-Z]{1,30}", "s");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readEoln();
    inf.readEof();
}
