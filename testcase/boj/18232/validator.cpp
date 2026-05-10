#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int maxM = min(1LL * N * (N - 1) / 2, 300000LL);
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    // 2. Read S, E
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int E = inf.readInt(1, N, "E");
    inf.readEoln();
    ensuref(S != E, "S (%d) and E (%d) must be different", S, E);

    // 3. Read M teleport edges, check for duplicates and loops
    set<pair<int,int>> teleport_edges;
    vector<vector<int>> teleport_adj(N + 1); // 1-based

    for (int i = 0; i < M; ++i) {
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readEoln();

        ensuref(x != y, "Teleport edge cannot be a loop at line %d: (%d, %d)", i + 3, x, y);

        int a = min(x, y), b = max(x, y);
        ensuref(!teleport_edges.count({a, b}),
            "Duplicate teleport edge at line %d: (%d, %d)", i + 3, x, y);

        teleport_edges.insert({a, b});
        teleport_adj[x].push_back(y);
        teleport_adj[y].push_back(x);
    }

    // 4. Build the full graph (adjacency list)
    // Each node has up to 2 "step" neighbors (X-1, X+1) and teleport neighbors
    vector<vector<int>> adj(N + 1); // 1-based

    for (int i = 1; i <= N; ++i) {
        if (i > 1) adj[i].push_back(i - 1);
        if (i < N) adj[i].push_back(i + 1);
        for (int y : teleport_adj[i]) {
            adj[i].push_back(y);
        }
    }

    // 5. Check that S can reach E (i.e., the answer always exists)
    // BFS from S to E
    vector<bool> visited(N + 1, false);
    queue<int> q;
    visited[S] = true;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    ensuref(visited[E], "E (%d) is not reachable from S (%d)", E, S);

    inf.readEof();
}
