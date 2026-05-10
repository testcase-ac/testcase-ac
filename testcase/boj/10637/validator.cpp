#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    int w;
    int idx;
};

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        p.resize(n + 1);
        r.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    vector<Edge> edges;
    edges.reserve(m);

    // to check simplicity (undirected, no loops, no multiple edges)
    // use n up to 1e5; adjacency as unordered set would be heavy,
    // but m <= 2e5 so we can store pairs in a vector and sort later.
    vector<pair<int,int>> pairs;
    pairs.reserve(m);

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int w = inf.readInt(0, 1000000, "w_i");
        inf.readEoln();

        ensuref(a != b, "Loop edge detected at index %d: (%d, %d)", i + 1, a, b);

        int u = a, v = b;
        if (u > v) swap(u, v);
        pairs.push_back({u, v});
        edges.push_back({u, v, w, i});
    }

    // check no multiple edges between any pair
    sort(pairs.begin(), pairs.end());
    for (int i = 1; i < m; ++i) {
        ensuref(!(pairs[i] == pairs[i - 1]),
                "Multiple edges detected between vertices (%d, %d)",
                pairs[i].first, pairs[i].second);
    }

    // Now check global property: for each i, MST of G_i exists iff G_i connected.
    // Statement guarantees nothing about existence, but does not impose extra
    // constraints other than simplicity, so we only need to ensure that
    // MST in original G exists or not? Problem does NOT guarantee that,
    // so we must NOT enforce connectivity of original graph.
    // However, we must ensure weights are non-negative (already via bounds)
    // so MST cost is well-defined where spanning tree exists.

    // Still, some problems explicitly say e.g. "it is guaranteed graph is connected".
    // Here, no such guarantee, so do NOT enforce connectivity.

    // However, we should make sure that for any connected component scenario,
    // our computations don't overflow if we later checked anything.
    // We won't compute all m MSTs (too heavy for validator), but we can
    // check that original G's MST cost, when it exists, fits in 64-bit.
    // Sum of up to 2e5 edges with w <= 1e6 is <= 2e11, fits in 64-bit.

    // Optional: compute MST of full G to detect absurd weights; here it's safe.
    // Also useful sanity: if MST uses all n-1 edges, fine; if not enough edges,
    // G is disconnected and that's allowed.

    {
        DSU dsu(n);
        vector<Edge> sorted = edges;
        sort(sorted.begin(), sorted.end(),
             [](const Edge &a, const Edge &b) {
                 if (a.w != b.w) return a.w < b.w;
                 return a.idx < b.idx;
             });
        long long mst_cost = 0;
        int used = 0;
        for (const auto &e : sorted) {
            if (dsu.unite(e.u, e.v)) {
                mst_cost += e.w;
                ++used;
            }
        }
        // if used != n-1, graph disconnected; allowed, no extra check
        // but still ensure no overflow (it cannot overflow by constraints)
        ensuref(mst_cost <= (long long)200000 * 1000000LL,
                "MST cost overflow sanity check failed (mst_cost=%lld)", mst_cost);
    }

    inf.readEof();
}
