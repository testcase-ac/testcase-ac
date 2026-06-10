#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    vector<int> p = inf.readInts(n, 1, 1000000, "p_i");
    inf.readEoln();

    ensuref(p[0] <= m, "p_1 must be at most m: p_1=%d, m=%d", p[0], m);
    for (int i = 1; i < n; ++i) {
        ensuref(p[i - 1] < p[i],
                "positions must be strictly increasing at index %d: %d >= %d",
                i + 1, p[i - 1], p[i]);
    }

    inf.readInts(n, 1, 10000, "x_i");
    inf.readEoln();
    inf.readEof();
}
