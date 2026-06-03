#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    inf.readLong(1LL, MAX_VALUE, "N");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "R");
    inf.readEoln();
    inf.readEof();
}
