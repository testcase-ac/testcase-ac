#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int flow;
    int super;
};

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return false;
        }
        if (rank[ra] < rank[rb]) {
            swap(ra, rb);
        }
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) {
            ++rank[ra];
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<vector<Edge>> graph(n + 1);
    DSU dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int x = inf.readInt(1, 100, "X_i");
        inf.readSpace();
        int t = inf.readInt(0, 1, "T_i");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at node %d", i, a);
        ensuref(edges.insert(minmax(a, b)).second,
                "duplicate edge %d between nodes %d and %d", i, a, b);
        ensuref(dsu.unite(a, b), "edge %d creates a cycle: %d %d", i, a, b);

        graph[a].push_back({b, x, t});
        graph[b].push_back({a, x, t});
    }

    for (int node = 2; node <= n; ++node) {
        ensuref(dsu.find(1) == dsu.find(node), "node %d is not connected to root 1", node);
    }

    vector<int> parent(n + 1, 0);
    vector<vector<Edge>> children(n + 1);
    vector<int> order;
    order.reserve(n);
    queue<int> q;
    parent[1] = -1;
    q.push(1);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);
        for (const Edge& edge : graph[node]) {
            if (edge.to == parent[node]) {
                continue;
            }
            ensuref(parent[edge.to] == 0,
                    "node %d has multiple parents after rooting at 1", edge.to);
            parent[edge.to] = node;
            children[node].push_back(edge);
            q.push(edge.to);
        }
    }

    for (int node = 1; node <= n; ++node) {
        if (children[node].empty()) {
            continue;
        }
        int sum = 0;
        for (const Edge& edge : children[node]) {
            sum += edge.flow;
        }
        ensuref(sum == 100, "outgoing flow sum from node %d is %d, expected 100", node, sum);
    }

    vector<int> need(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        need[i] = inf.readInt(-1, 10, "K_i");
        bool leaf = children[i].empty();
        ensuref((leaf && need[i] >= 1) || (!leaf && need[i] == -1),
                "K_%d is %d but node %d is %s",
                i,
                need[i],
                i,
                leaf ? "a leaf" : "not a leaf");
    }
    inf.readEoln();
    inf.readEof();

    vector<double> required(n + 1, 0.0);
    reverse(order.begin(), order.end());
    for (int node : order) {
        if (children[node].empty()) {
            required[node] = need[node];
            continue;
        }
        double nodeRequired = 0.0;
        for (const Edge& edge : children[node]) {
            double childRequired = required[edge.to];
            double ratio = edge.flow / 100.0;
            double throughRegular = childRequired / ratio;
            double throughSuper = edge.super == 1 ? sqrt(childRequired) / ratio : throughRegular;
            nodeRequired = max(nodeRequired, min(throughRegular, throughSuper));
        }
        required[node] = nodeRequired;
    }

    ensuref(required[1] <= 2000000000.0 + 1e-7,
            "required L is %.12f, exceeding 2e9", required[1]);

    return 0;
}
