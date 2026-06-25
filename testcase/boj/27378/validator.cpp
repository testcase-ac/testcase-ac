#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxValue = 1LL << 60;

    long long n = inf.readLong(1LL, kMaxValue, "N");
    inf.readSpace();
    inf.readInt(0, 60, "K");
    inf.readSpace();
    long long a = inf.readLong(1LL, kMaxValue, "A");
    inf.readSpace();
    long long b = inf.readLong(a, kMaxValue, "B");
    inf.readEoln();
    inf.readEof();

    (void)n;
}
