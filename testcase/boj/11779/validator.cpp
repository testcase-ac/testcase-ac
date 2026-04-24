#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read number of buses (edges)
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Prepare adjacency list for reachability check
    vector<vector<int>> adj(n+1);

    // Read m edges
    for (int i = 1; i <= m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(0, 100000, "w_i");
        inf.readEoln();

        // According to statement, buses go to a different city
        ensuref(u != v, "Loop detected at edge %d: from %d to %d", i, u, v);

        // Build directed graph for reachability
        adj[u].push_back(v);
    }

    // Read source and destination
    int A = inf.readInt(1, n, "src");
    inf.readSpace();
    int B = inf.readInt(1, n, "dst");
    inf.readEoln();

    // Check reachability from A to B
    vector<char> seen(n+1, 0);
    queue<int> q;
    seen[A] = 1;
    q.push(A);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                q.push(v);
            }
        }
    }
    ensuref(seen[B], "No path from src=%d to dst=%d", A, B);

    inf.readEof();
    return 0;
}
