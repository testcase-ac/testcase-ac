#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    int zero_count = 0;
    int one_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int cell = inf.readInt(0, 1, "cell");
            if (cell == 0) {
                ++zero_count;
            } else {
                ++one_count;
            }
        }
        inf.readEoln();
    }

    ensuref(zero_count >= 1, "the grid must contain at least one 0");
    ensuref(one_count >= 1, "the grid must contain at least one 1");

    inf.readEof();
    return 0;
}
