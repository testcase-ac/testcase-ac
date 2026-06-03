#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000LL;

    inf.readLong(1LL, MAX_VALUE, "a");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "r");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "n");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "mod");
    inf.readEoln();
    inf.readEof();
}
