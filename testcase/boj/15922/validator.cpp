#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    int prevX = -1000000001;
    int prevY = -1000000001;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "x");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y");
        inf.readEoln();

        ensuref(x < y, "segment %d must satisfy x < y, got %d >= %d", i + 1, x, y);
        ensuref(prevX < x || (prevX == x && prevY <= y),
                "segments must be sorted by x then y at index %d", i + 1);

        prevX = x;
        prevY = y;
    }

    inf.readEof();
}
