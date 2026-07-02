#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bounds. Cap n and m at practical
    // graph-input sizes, while also enforcing the stated distinct-pair limit.
    const int maxN = 100000;
    const int maxM = 1000000;

    int n = inf.readInt(0, maxN, "n");
    inf.readSpace();

    long long completeGraphEdges = 1LL * n * (n - 1) / 2;
    int mLimit = static_cast<int>(min<long long>(maxM, completeGraphEdges));
    int m = inf.readInt(0, mLimit, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: (%d, %d)", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate dislike pair at edge %d: (%d, %d)", i, a, b);
    }

    inf.readEof();
}
