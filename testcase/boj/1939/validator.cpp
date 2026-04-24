#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Build adjacency for connectivity check
    vector<vector<int>> adj(N+1);

    // Read M bridges
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        long long C = inf.readLong(1LL, 1000000000LL, "C_i");
        inf.readEoln();

        // No loops allowed (A != B)
        ensuref(A != B,
                "Bridge %d is a loop: both endpoints are %d", i+1, A);

        // Add to adjacency (undirected)
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    // Read the two distinct factory locations
    int S = inf.readInt(1, N, "factory1");
    inf.readSpace();
    int T = inf.readInt(1, N, "factory2");
    inf.readEoln();
    ensuref(S != T,
            "Factory islands must be distinct: both are %d", S);

    // Check that there is a path from S to T
    vector<char> vis(N+1, 0);
    queue<int> q;
    vis[S] = 1;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    ensuref(vis[T],
            "No path exists between factory islands %d and %d", S, T);

    // Final EOF
    inf.readEof();
    return 0;
}
