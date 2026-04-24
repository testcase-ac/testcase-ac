#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 20000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50000, "M");
    inf.readEoln();

    // Read edges and build adjacency
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i + 1, a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Check connectivity from node 1 via BFS
    vector<char> vis(N + 1, 0);
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    int reached = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                reached++;
                q.push(v);
            }
        }
    }
    ensuref(reached == N,
            "Graph is not connected: only %d out of %d nodes are reachable from node 1",
            reached, N);

    inf.readEof();
    return 0;
}
