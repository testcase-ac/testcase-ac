#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long kMaxCoordinate = 1LL << 60;

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        inf.readLong(0LL, kMaxCoordinate, "x");
        inf.readSpace();
        inf.readLong(0LL, kMaxCoordinate, "y");
        inf.readEoln();
    }

    inf.readEof();
}
