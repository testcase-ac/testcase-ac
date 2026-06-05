#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long MAX_CARD = (1LL << 31) - 1;

    inf.readLong(0LL, MAX_CARD, "a");
    inf.readSpace();
    inf.readLong(0LL, MAX_CARD, "b");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "n");
    inf.readEoln();
    inf.readEof();
}
