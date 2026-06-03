#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5, "m");
    inf.readSpace();
    int k = inf.readInt(1, 3, "k");
    inf.readEoln();

    int minD = max(m, k) + 1;
    for (int i = 0; i < n; ++i) {
        int d = inf.readInt(minD, 1000, "d_i");
        inf.readEoln();
        ensuref(m < d, "d_%d must be greater than m: m=%d, d=%d", i + 1, m, d);
        ensuref(k < d, "d_%d must be greater than k: k=%d, d=%d", i + 1, k, d);
    }

    inf.readEof();
}
