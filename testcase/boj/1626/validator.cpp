#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
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
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }
};

struct Edge {
    int a;
    int b;
    int w;
    bool in_mst = false;
};

array<int, 2> mergeTop(array<int, 2> left, array<int, 2> right) {
    array<int, 2> result = {-1, -1};
    for (int value : {left[0], left[1], right[0], right[1]}) {
        if (value < 0 || value == result[0] || value == result[1]) {
            continue;
        }
        if (value > result[0]) {
            result[1] = result[0];
            result[0] = value;
        } else if (value > result[1]) {
            result[1] = value;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(1, 50000, "V");
    inf.readSpace();
    int e = inf.readInt(1, 200000, "E");
    inf.readEoln();

    vector<Edge> edges;
    edges.reserve(e);
    for (int i = 1; i <= e; ++i) {
        int a = inf.readInt(1, v, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, v, "B_i");
        inf.readSpace();
        int w = inf.readInt(0, 100000, "W_i");
        inf.readEoln();

        // CHECK: The statement does not explicitly forbid self-loops or
        // duplicate undirected edges, so the validator accepts them.
        edges.push_back({a, b, w});
    }

    vector<int> order(e);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int lhs, int rhs) {
        return edges[lhs].w < edges[rhs].w;
    });

    DSU dsu(v);
    long long mst_weight = 0;
    int used_edges = 0;
    vector<vector<pair<int, int>>> tree(v + 1);
    for (int id : order) {
        Edge& edge = edges[id];
        if (!dsu.unite(edge.a, edge.b)) {
            continue;
        }

        edge.in_mst = true;
        mst_weight += edge.w;
        ++used_edges;
        tree[edge.a].push_back({edge.b, edge.w});
        tree[edge.b].push_back({edge.a, edge.w});
    }

    long long second_mst_weight = LLONG_MAX;
    if (used_edges == v - 1 && v > 1) {
        int log = 1;
        while ((1 << log) <= v) {
            ++log;
        }

        vector<int> depth(v + 1, -1);
        vector<vector<int>> parent(log, vector<int>(v + 1, 0));
        vector<vector<array<int, 2>>> best(
            log, vector<array<int, 2>>(v + 1, {-1, -1}));

        queue<int> q;
        depth[1] = 0;
        q.push(1);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto [next, weight] : tree[cur]) {
                if (depth[next] != -1) {
                    continue;
                }
                depth[next] = depth[cur] + 1;
                parent[0][next] = cur;
                best[0][next] = {weight, -1};
                q.push(next);
            }
        }

        for (int level = 1; level < log; ++level) {
            for (int node = 1; node <= v; ++node) {
                int mid = parent[level - 1][node];
                parent[level][node] = parent[level - 1][mid];
                best[level][node] = mergeTop(
                    best[level - 1][node],
                    best[level - 1][mid]);
            }
        }

        auto pathTopWeights = [&](int a, int b) {
            array<int, 2> result = {-1, -1};
            if (depth[a] < depth[b]) {
                swap(a, b);
            }

            int diff = depth[a] - depth[b];
            for (int level = 0; level < log; ++level) {
                if ((diff & (1 << level)) != 0) {
                    result = mergeTop(result, best[level][a]);
                    a = parent[level][a];
                }
            }

            if (a == b) {
                return result;
            }

            for (int level = log - 1; level >= 0; --level) {
                if (parent[level][a] != parent[level][b]) {
                    result = mergeTop(result, best[level][a]);
                    result = mergeTop(result, best[level][b]);
                    a = parent[level][a];
                    b = parent[level][b];
                }
            }

            result = mergeTop(result, best[0][a]);
            result = mergeTop(result, best[0][b]);
            return result;
        };

        for (const Edge& edge : edges) {
            if (edge.in_mst || edge.a == edge.b) {
                continue;
            }

            array<int, 2> top = pathTopWeights(edge.a, edge.b);
            int removed = -1;
            if (top[0] >= 0 && top[0] < edge.w) {
                removed = top[0];
            } else if (top[0] == edge.w && top[1] >= 0) {
                removed = top[1];
            }

            if (removed >= 0) {
                long long candidate = mst_weight + edge.w - removed;
                if (candidate > mst_weight) {
                    second_mst_weight = min(second_mst_weight, candidate);
                }
            }
        }

        if (second_mst_weight != LLONG_MAX) {
            ensuref(second_mst_weight <= 2147483647LL,
                    "second MST weight %lld exceeds 2^31-1",
                    second_mst_weight);
        }
    }

    inf.readEof();
}
