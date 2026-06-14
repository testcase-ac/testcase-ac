#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<int> lengths(m);
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        lengths[i] = inf.readInt(2, 20, "length_i");
        ensuref(lengths[i] % 2 == 0,
                "column info length must be even at column %d: %d",
                i + 1, lengths[i]);
    }
    inf.readEoln();

    for (int col = 0; col < m; ++col) {
        int previousBottom = 0;
        for (int j = 0; j < lengths[col] / 2; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int top = inf.readInt(1, n, "top");
            inf.readSpace();
            int bottom = inf.readInt(1, n, "bottom");

            ensuref(top <= bottom,
                    "interval top is below bottom at column %d interval %d: %d > %d",
                    col + 1, j + 1, top, bottom);
            ensuref(previousBottom < top,
                    "intervals must be strictly increasing and disjoint at column %d interval %d: previous bottom %d, top %d",
                    col + 1, j + 1, previousBottom, top);

            previousBottom = bottom;
        }
        inf.readEoln();
    }

    inf.readEof();
}
