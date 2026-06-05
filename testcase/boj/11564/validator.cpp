#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long MIN_COORD = -1000000000000000000LL;
    constexpr long long MAX_COORD = 1000000000000000000LL;

    inf.readLong(1LL, MAX_COORD, "k");
    inf.readSpace();
    long long a = inf.readLong(MIN_COORD, MAX_COORD, "a");
    inf.readSpace();
    long long b = inf.readLong(a, MAX_COORD, "b");
    inf.readEoln();
    inf.readEof();
}
