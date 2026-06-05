#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    inf.readLong(1LL, MAX_VALUE, "A");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "B");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "C");
    inf.readEoln();
    inf.readEof();
}
