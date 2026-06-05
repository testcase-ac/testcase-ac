#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxValue = 1LL << 60;

    long long a = inf.readLong(0LL, kMaxValue - 1, "a");
    inf.readSpace();
    long long b = inf.readLong(a + 1, kMaxValue, "b");
    inf.readEoln();

    inf.readEof();
}
