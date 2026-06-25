#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d = inf.readInt(1, 256, "d");
    inf.readSpace();
    int k = inf.readInt(1, d, "k");
    inf.readEoln();

    int previousRed = -1;
    for (int i = 0; i < d; ++i) {
        int r = inf.readInt(0, 255, "r");
        inf.readSpace();
        inf.readLong(1LL, 67108864LL, "p");
        inf.readEoln();

        ensuref(r > previousRed,
                "red values must be strictly increasing at row %d: previous=%d current=%d",
                i + 1,
                previousRed,
                r);
        previousRed = r;
    }

    inf.readEof();
}
