#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, B
    int N = inf.readInt(2, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(N-1, 100000, "M");
    inf.readSpace();
    int B = inf.readInt(1, 25000, "B");
    inf.readEoln();

    ensuref(2*B <= N, "Constraint violated: 2*B (%d) > N (%d)", 2*B, N);

    // Read M edges
    struct Edge {
        int to;
        int len;
    };
    vector<vector<Edge>> adj(N+1); // 1-based

    for (int i = 0; i < M; ++i) {
        int R = inf.readInt(1, N, "R_i");
        inf.readSpace();
        int S = inf.readInt(1, N, "S_i");
        inf.readSpace();
        int L = inf.readInt(1, 2000, "L_i");
        inf.readEoln();

        // Allow self-loops and multiple edges as not forbidden in statement
        adj[R].push_back({S, L});
        adj[S].push_back({R, L});
    }

    // Read B queries
    vector<int> P(B), Q(B);
    for (int i = 0; i < B; ++i) {
        P[i] = inf.readInt(1, N, "P_i");
        inf.readSpace();
        Q[i] = inf.readInt(1, N, "Q_i");
        inf.readEoln();
    }

    // Check that the graph is connected (the barn at pasture 1 connects to every pasture)
    // Use BFS from node 1
    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const Edge& e : adj[u]) {
            if (!vis[e.to]) {
                vis[e.to] = true;
                q.push(e.to);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d of %d pastures reachable from barn (pasture 1)", cnt, N);

    inf.readEof();
}
