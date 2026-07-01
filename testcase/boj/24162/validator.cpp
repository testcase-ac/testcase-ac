#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readSpace();
    // CHECK: The statement omits an explicit m bound, but says each pair of
    // toll posts has at most one road, so m is bounded by the simple graph size.
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        inf.readInt(-10000, 10000, "y_i");
        inf.readEoln();
    }

    set<pair<int, int>> roads;
    for (int j = 1; j <= m; ++j) {
        int a = inf.readInt(1, n - 1, "a_j");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "b_j");
        inf.readSpace();
        inf.readInt(0, 10000, "c_j");
        inf.readEoln();

        ensuref(roads.emplace(a, b).second,
                "duplicate road at index %d: (%d, %d)", j, a, b);
    }

    inf.readEof();
}
