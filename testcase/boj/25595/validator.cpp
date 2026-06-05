#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int startCount = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int cell = inf.readInt(0, 2, "cell");
            if (cell == 2) {
                ++startCount;
            }

            if (c + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one start position, found %d", startCount);

    inf.readEof();
    return 0;
}
