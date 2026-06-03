#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    int count1 = 0;
    int count2 = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int cell = inf.readInt(-1, 2, "cell");
            ensuref(cell != 3, "cell (%d, %d) has invalid state 3", i + 1, j + 1);

            if (cell == 1) {
                ++count1;
            } else if (cell == 2) {
                ++count2;
            }

            if (j + 1 == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(count1 == 1, "expected exactly one cell infected by virus 1, found %d", count1);
    ensuref(count2 == 1, "expected exactly one cell infected by virus 2, found %d", count2);

    inf.readEof();
}
