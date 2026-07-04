#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxValue = 999999999999999999LL;

    inf.readLong(1LL, maxValue, "a");
    inf.readSpace();
    inf.readLong(1LL, maxValue, "b");
    inf.readSpace();
    inf.readLong(1LL, maxValue, "c");
    inf.readSpace();
    inf.readLong(1LL, maxValue, "d");
    inf.readEoln();
    inf.readEof();
}
