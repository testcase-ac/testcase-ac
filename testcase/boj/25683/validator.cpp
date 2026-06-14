#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) {
        r[i] = inf.readInt(1, 10000, "r_i");
        inf.readSpace();
        c[i] = inf.readInt(1, 10000, "c_i");
        inf.readEoln();

        if (i > 0) {
            ensuref(c[i - 1] == r[i],
                    "matrix sizes are not chain-compatible at index %d: c_%d=%d, r_%d=%d",
                    i + 1, i, c[i - 1], i + 1, r[i]);
            ensuref(r[i - 1] >= r[i],
                    "row dimensions are not nonincreasing at index %d: r_%d=%d, r_%d=%d",
                    i + 1, i, r[i - 1], i + 1, r[i]);
            ensuref(c[i - 1] >= c[i],
                    "column dimensions are not nonincreasing at index %d: c_%d=%d, c_%d=%d",
                    i + 1, i, c[i - 1], i + 1, c[i]);
        }
    }

    inf.readEof();
}
