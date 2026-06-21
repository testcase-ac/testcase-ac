#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long maxEdges = min(200000LL, 1LL * n * (n - 1) / 2);
    int m = inf.readInt(0, maxEdges, "M");
    inf.readEoln();

    vector<long long> heights = inf.readLongs(n, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    set<long long> seenHeights;
    for (int i = 0; i < n; ++i) {
        ensuref(seenHeights.insert(heights[i]).second,
                "duplicate height at index %d: %lld", i + 1, heights[i]);
    }

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u < v, "edge index %d must satisfy u < v: (%d, %d)", i + 1, u, v);
        ensuref(edges.insert({u, v}).second,
                "duplicate edge at index %d: (%d, %d)", i + 1, u, v);
    }

    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<int> open = inf.readInts(k, 1, n, "a_i");
    inf.readEoln();

    set<int> seenOpen;
    for (int i = 0; i < k; ++i) {
        ensuref(seenOpen.insert(open[i]).second,
                "duplicate unblocked drain at index %d: %d", i + 1, open[i]);
    }

    inf.readEof();
}
