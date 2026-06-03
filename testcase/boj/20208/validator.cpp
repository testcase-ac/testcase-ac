#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10, "m");
    inf.readSpace();
    int h = inf.readInt(1, 10, "h");
    inf.readEoln();

    int home_count = 0;
    int milk_count = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int cell = inf.readInt(0, 2, "cell");
            if (cell == 1) {
                ++home_count;
            } else if (cell == 2) {
                ++milk_count;
            }

            if (c + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(home_count == 1, "expected exactly one home, found %d", home_count);
    ensuref(milk_count <= 10, "expected at most 10 milk cells, found %d", milk_count);

    inf.readEof();
}
