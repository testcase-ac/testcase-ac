#include "testlib.h"
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    vector<int> weights = inf.readInts(N, 1, 1000000, "weights");
    inf.readEoln();

    vector<vector<int>> adj(N + 1);
    set<pair<int,int>> edges;
    for (int i = 0; i < N - 1; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected between %d and %d", a, b);
        edges.insert({a, b});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const int LOG = 18;
    vector<bool> visited(N + 1, false);
    vector<int> depth(N + 1, 0);
    vector<vector<int>> parent(LOG, vector<int>(N + 1, 0));
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                depth[nxt] = depth[cur] + 1;
                parent[0][nxt] = cur;
                q.push(nxt);
                cnt++;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    for (int j = 1; j < LOG; ++j) {
        for (int v = 1; v <= N; ++v) {
            parent[j][v] = parent[j - 1][parent[j - 1][v]];
        }
    }

    auto lca = [&](int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; ++j) {
            if ((diff >> j) & 1) {
                u = parent[j][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int j = LOG - 1; j >= 0; --j) {
            if (parent[j][u] != parent[j][v]) {
                u = parent[j][u];
                v = parent[j][v];
            }
        }
        return parent[0][u];
    };

    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "query_u");
        inf.readSpace();
        int v = inf.readInt(1, N, "query_v");
        inf.readSpace();
        int k = inf.readInt(1, N, "query_k");
        inf.readEoln();

        int ancestor = lca(u, v);
        int pathLength = depth[u] + depth[v] - 2 * depth[ancestor] + 1;
        ensuref(k <= pathLength,
                "query %d has k=%d, but path %d-%d contains only %d vertices",
                i + 1, k, u, v, pathLength);
    }

    inf.readEof();
}
