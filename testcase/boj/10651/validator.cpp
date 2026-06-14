#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "T");
    inf.readEoln();

    long long previousPosition = -1;
    for (int i = 0; i < n; ++i) {
        long long position = inf.readLong(0LL, 1000000000LL, "position");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "speed");
        inf.readEoln();

        ensuref(position > previousPosition,
                "positions must be distinct and increasing at cow %d: previous=%lld, current=%lld",
                i + 1, previousPosition, position);
        previousPosition = position;
    }

    inf.readEof();
}
