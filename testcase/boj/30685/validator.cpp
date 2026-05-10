#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 300000, "N");
    inf.readEoln();

    // 2. Read N lines of (x_i, h_i)
    set<int> x_set;
    vector<int> x(N);
    vector<int> h(N);
    for (int i = 0; i < N; ++i) {
        x[i] = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        h[i] = inf.readInt(1, 1000000000 - 1, "h_i");
        inf.readEoln();

        // x_i must be unique
        ensuref(x_set.count(x[i]) == 0, "x_i is not unique at index %d: %d", i+1, x[i]);
        x_set.insert(x[i]);

        // h_i must be odd
        ensuref(h[i] % 2 == 1, "h_i is not odd at index %d: %d", i+1, h[i]);
    }

    inf.readEof();
}
