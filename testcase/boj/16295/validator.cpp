#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "m");
    inf.readEoln();

    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        x[i] = inf.readInt(0, 1000000000, "x_i");
        if (i > 0) {
            ensuref(x[i - 1] < x[i],
                    "positions must be strictly increasing: x_%d=%d, x_%d=%d",
                    i, x[i - 1], i + 1, x[i]);
        }
    }
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000000, "l_i");
    }
    inf.readEoln();

    inf.readEof();
}
