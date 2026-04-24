#include "testlib.h"
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, c
    int n = inf.readInt(1, 25000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 50000, "m");
    inf.readSpace();
    int c = inf.readInt(0, 1000, "c");
    inf.readEoln();

    // Prepare adjacency list for reachability check
    vector<vector<int>> adj(n + 1);

    // Read edges
    for (int i = 0; i < m; i++) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int t = inf.readInt(1, 10000, "t_i");
        inf.readEoln();

        // No loops allowed
        ensuref(x != y, "Edge %d has a loop: (%d -> %d)", i, x, y);

        // Build undirected graph
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // Read starting intersections of commuters
    if (c > 0) {
        vector<int> starts = inf.readInts(c, 1, n, "start_i");
        inf.readEoln();
    } else {
        // Even if c == 0, there should be a blank (empty) line for the starts
        inf.readEoln();
    }

    // Check global property: all intersections must reach downtown (node 1)
    vector<char> vis(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                cnt++;
                q.push(v);
            }
        }
    }
    ensuref(cnt == n, "Not all intersections reachable to downtown: reached %d out of %d", cnt, n);

    inf.readEof();
    return 0;
}
