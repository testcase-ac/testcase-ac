#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);
    unordered_set<uint64_t> seen;
    seen.reserve(static_cast<size_t>(m) * 2);

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop: %d %d", i, u, v);

        int a = min(u, v);
        int b = max(u, v);
        uint64_t key = (static_cast<uint64_t>(a) << 32) | static_cast<uint64_t>(b);
        ensuref(seen.insert(key).second, "edge %d duplicates edge %d %d", i, a, b);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<char> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;

    int reachable = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++reachable;

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    ensuref(reachable == n, "graph is not connected: only %d of %d rooms are reachable", reachable, n);
    ensuref(m >= n, "connected graph has no cycle: N=%d M=%d", n, m);

    inf.readEof();
}
