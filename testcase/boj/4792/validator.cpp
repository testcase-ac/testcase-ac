#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = 0;
    while (true) {
        // Read header with relaxed bounds to allow terminator 0 0 0
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 1000 * 999 / 2, "m");
        inf.readSpace();
        int k = inf.readInt(0, 1000, "k");
        inf.readEoln();

        // Check for terminator
        if (n == 0 && m == 0 && k == 0) {
            break;
        }

        // New test case
        testCount++;
        setTestCase(testCount);

        // Validate header constraints
        ensuref(n >= 2 && n <= 1000,
                "n must be between 2 and 1000, got n=%d", n);
        // m must fit in a simple undirected graph
        long long maxEdges = (long long)n * (n - 1) / 2;
        ensuref(m >= 0 && m <= maxEdges,
                "m must satisfy 0 <= m <= n*(n-1)/2, got m=%d for n=%d", m, n);
        ensuref(k >= 0 && k < n,
                "k must satisfy 0 <= k < n, got k=%d with n=%d", k, n);

        // Prepare for edge validation
        vector<vector<int>> adj(n + 1);
        set<pair<int,int>> seenEdges;

        // Read edges
        for (int i = 0; i < m; i++) {
            // color token: 'R' or 'B'
            string c = inf.readToken("[RB]", "c_i");
            inf.readSpace();
            int u = inf.readInt(1, n, "f_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "t_i");
            inf.readEoln();

            // No loops
            ensuref(u != v,
                    "Loop detected at edge index %d: (%d, %d)", i, u, v);
            // No multiple edges
            int a = min(u, v), b = max(u, v);
            pair<int,int> e = make_pair(a, b);
            ensuref(!seenEdges.count(e),
                    "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
            seenEdges.insert(e);

            // Build adjacency for connectivity check
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check connectivity by BFS
        vector<char> vis(n + 1, 0);
        queue<int> q;
        q.push(1);
        vis[1] = 1;
        int seenCount = 1;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int y : adj[x]) {
                if (!vis[y]) {
                    vis[y] = 1;
                    seenCount++;
                    q.push(y);
                }
            }
        }
        ensuref(seenCount == n,
                "Graph is not connected: only %d/%d nodes reachable", seenCount, n);
    }

    // Check number of test cases limit
    ensuref(testCount <= 100000,
            "Number of test cases must not exceed 100000, got %d", testCount);

    inf.readEof();
    return 0;
}
