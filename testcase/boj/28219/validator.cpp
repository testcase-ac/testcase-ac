#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;
    int merges = 0;

    explicit DSU(int n): parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] != v) parent[v] = find(parent[v]);
        return parent[v];
    }

    bool unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) ++rank[ra];
        ++merges;
        return true;
    }
};

pair<int, int> farthestFrom(int start, const vector<vector<int>>& graph) {
    vector<int> dist(graph.size(), -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    int farthest = start;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] > dist[farthest]) farthest = v;
        for (int to : graph[v]) {
            if (dist[to] != -1) continue;
            dist[to] = dist[v] + 1;
            q.push(to);
        }
    }

    return {farthest, dist[farthest]};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "k");
    inf.readEoln();

    DSU dsu(n);
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(x != y, "edge %d is a loop at village %d", i, x);
        ensuref(dsu.unite(x, y), "edge %d creates a cycle or duplicate: %d %d", i, x, y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    ensuref(dsu.merges == n - 1, "roads do not form a connected tree");

    auto first = farthestFrom(1, graph);
    auto second = farthestFrom(first.first, graph);
    ensuref(second.second >= k, "tree diameter %d is less than k=%d", second.second, k);

    inf.readEof();
}
