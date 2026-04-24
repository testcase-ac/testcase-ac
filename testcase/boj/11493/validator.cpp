#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(1, 500, "n");
        inf.readSpace();
        // m between n-1 and n(n-1)/2
        int maxm = n * (n - 1) / 2;
        int m = inf.readInt(n - 1, maxm, "m");
        inf.readEoln();

        // Read edges, check loops, duplicates, build adjacency
        vector<vector<int>> adj(n + 1);
        set<pair<int,int>> seen;
        for (int i = 0; i < m; i++) {
            int x = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, n, "y_i");
            inf.readEoln();

            // Check ordering to forbid loops and enforce x<y
            ensuref(x < y,
                    "Invalid edge at index %d: endpoints must satisfy x < y, got (%d, %d)",
                    i, x, y);
            // Check duplicates
            pair<int,int> e = make_pair(x, y);
            ensuref(!seen.count(e),
                    "Multiple edges detected between %d and %d", x, y);
            seen.insert(e);

            // Build adjacency
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        // Check connectivity via BFS from node 1
        vector<char> vis(n + 1, false);
        queue<int> q;
        vis[1] = true;
        q.push(1);
        int cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    cnt++;
                    q.push(v);
                }
            }
        }
        ensuref(cnt == n,
                "Graph is not connected in test case %d: only %d of %d nodes reachable",
                tc, cnt, n);

        // Read vertex colors: 0 or 1
        vector<int> vertex_color = inf.readInts(n, 0, 1, "vertex_color_i");
        inf.readEoln();

        // Read coin colors: 0 or 1
        vector<int> coin_color = inf.readInts(n, 0, 1, "coin_color_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
