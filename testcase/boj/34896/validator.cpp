#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    vector<int> x = inf.readInts(n, -100000000, 100000000, "X_i");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        ensuref(positions.insert(x[i]).second,
                "duplicate position at index %d: %d", i + 1, x[i]);
    }

    vector<int> c = inf.readInts(n, 1, 10000, "C_i");
    inf.readEoln();

    int minCost = c[0];
    for (int cost : c) {
        minCost = min(minCost, cost);
    }

    int b = inf.readInt(minCost, 10000000, "B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
