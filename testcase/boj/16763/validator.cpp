#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(2, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read edges and build adjacency for connectivity check
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int t = inf.readInt(1, 10000, "t_i");
        inf.readEoln();

        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);
        // multiple edges allowed by problem statement
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Read haybales
    for (int i = 0; i < K; i++) {
        int p = inf.readInt(1, N, "h_i_node");
        inf.readSpace();
        long long y = inf.readLong(1LL, 1000000000LL, "y_i");
        inf.readEoln();
        // multiple haybales per pasture allowed
        (void)p; (void)y;
    }

    // Check that every pasture can reach the barn at pasture N
    vector<char> vis(N + 1, 0);
    queue<int> q;
    vis[N] = 1;
    q.push(N);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        ensuref(vis[i],
                "Pasture %d cannot reach the barn (pasture %d unreachable)", i, N);
    }

    inf.readEof();
    return 0;
}
