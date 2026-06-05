#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_X = -1000000000000000000LL;
    const long long MAX_X = 1000000000000000000LL;

    int q = inf.readInt(1, 111222, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        long long x = inf.readLong(MIN_X, MAX_X, "x");
        inf.readSpace();
        char direction = inf.readChar();
        ensuref(direction == '^' || direction == 'v',
                "query %d has invalid direction '%c'", i, direction);
        inf.readEoln();
    }

    inf.readEof();
}
