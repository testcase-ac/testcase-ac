#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCount = 200000;
    const long long maxValue = 1000000000LL;

    int n = inf.readInt(2, maxCount, "n");
    inf.readSpace();
    int m = inf.readInt(2, maxCount, "m");
    inf.readSpace();
    int k = inf.readInt(2, maxCount, "k");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readLong(1LL, maxValue, "c_i");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at vertex %d", i, a);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate undirected edge %d: %d %d", i, a, b);
    }

    int s = inf.readInt(1, maxCount, "s");
    inf.readEoln();

    for (int i = 1; i <= s; ++i) {
        inf.readInt(1, n, "v_i");
        inf.readSpace();
        inf.readLong(1LL, maxValue, "h_i");
        inf.readSpace();
        inf.readLong(1LL, maxValue, "t_i");
        inf.readEoln();
    }

    inf.readLong(1LL, maxValue, "V");
    inf.readEoln();
    inf.readEof();
}
