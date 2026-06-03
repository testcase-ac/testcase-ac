#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
    bool inMst = false;
};

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int maxEdgeOnPath(int from, int target,
                  const vector<vector<pair<int, int>>>& tree) {
    vector<int> parent(tree.size(), -1);
    vector<int> maxEdge(tree.size(), -1);
    vector<int> stack = {from};
    parent[from] = from;

    while (!stack.empty()) {
        int cur = stack.back();
        stack.pop_back();
        if (cur == target) {
            return maxEdge[cur];
        }
        for (auto [next, weight] : tree[cur]) {
            if (parent[next] != -1) {
                continue;
            }
            parent[next] = cur;
            maxEdge[next] = max(maxEdge[cur], weight);
            stack.push_back(next);
        }
    }

    ensuref(false, "MST path missing between %d and %d", from, target);
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "k");
    inf.readEoln();

    long long maxSimpleEdges = 1LL * n * (n - 1) / 2;
    ensuref(k <= maxSimpleEdges, "too many edges for a simple graph: k=%d n=%d", k, n);

    vector<Edge> edges;
    edges.reserve(k);
    set<pair<int, int>> seenEdges;

    for (int i = 0; i < k; ++i) {
        int a = inf.readInt(0, n - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b");
        inf.readSpace();
        int c = inf.readInt(1, 1000000, "c");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d", i + 1, a);
        auto normalized = minmax(a, b);
        ensuref(seenEdges.insert(normalized).second,
                "duplicate edge at edge %d: %d %d", i + 1, a, b);
        edges.push_back({a, b, c});
    }

    vector<int> order(k);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int lhs, int rhs) {
        return tuple(edges[lhs].w, edges[lhs].u, edges[lhs].v) <
               tuple(edges[rhs].w, edges[rhs].u, edges[rhs].v);
    });

    Dsu dsu(n);
    vector<vector<pair<int, int>>> mst(n);
    int mstEdges = 0;
    for (int idx : order) {
        Edge& edge = edges[idx];
        if (!dsu.unite(edge.u, edge.v)) {
            continue;
        }
        edge.inMst = true;
        ++mstEdges;
        mst[edge.u].push_back({edge.v, edge.w});
        mst[edge.v].push_back({edge.u, edge.w});
    }

    ensuref(mstEdges == n - 1, "graph is not connected: mst_edges=%d n=%d", mstEdges, n);

    for (int i = 0; i < k; ++i) {
        const Edge& edge = edges[i];
        if (edge.inMst) {
            continue;
        }
        int pathMax = maxEdgeOnPath(edge.u, edge.v, mst);
        ensuref(edge.w > pathMax,
                "MST is not unique: non-tree edge %d has weight %d and path max %d",
                i + 1, edge.w, pathMax);
    }

    inf.readEof();
}
