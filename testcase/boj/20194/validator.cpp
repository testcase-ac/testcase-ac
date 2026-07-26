#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    long long l = inf.readLong(1LL, 1000000000000LL, "l");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "r");
    inf.readEoln();

    long long previous = -1;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        long long position = inf.readLong(0LL, l, "position");
        ensuref(previous <= position,
                "positions must be nondecreasing: position %d is %lld after %lld",
                i + 1, position, previous);
        previous = position;
    }
    inf.readEoln();
    inf.readEof();
}
