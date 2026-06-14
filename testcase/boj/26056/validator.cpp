#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long kMaxValue = 100000000000000LL;

    long long s = inf.readLong(1LL, kMaxValue, "S");
    inf.readSpace();
    long long t = inf.readLong(s, kMaxValue, "T");
    inf.readEoln();
    inf.readEof();
}
