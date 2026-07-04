#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500, "M");
    inf.readSpace();
    int k = inf.readInt(1, min(n * m, 500), "K");
    inf.readEoln();

    vector<int> p = inf.readInts(n, 0, m, "P_i");
    inf.readEoln();

    vector<int> b = inf.readInts(m + 1, 0, 100000, "B_i");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        ensuref(b[i] <= b[i + 1], "B must be nondecreasing at index %d: %d > %d",
                i, b[i], b[i + 1]);
    }

    int owned = accumulate(p.begin(), p.end(), 0);
    ensuref(k <= n * m - owned,
            "K exceeds remaining pictures: K=%d, remaining=%d", k, n * m - owned);

    inf.readEof();
}
