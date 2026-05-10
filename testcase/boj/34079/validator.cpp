#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int maxM = min(1LL * N * (N - 1) / 2, 300000LL);
    int minM = N - 1;
    int M = inf.readInt(minM, (int)maxM, "M");
    inf.readEoln();

    // Prepare to read edges and check for duplicates/loops
    set<pair<int, int>> edges;
    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i + 1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected at edge index %d: (%d, %d)", i + 1, u, v);
        edges.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check that the graph is connected (BFS from node 1)
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push(nxt);
                cnt++;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    inf.readEof();
}
