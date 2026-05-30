#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int maxM = min(100000LL, 1LL * n * (n - 1) / 2);
    int m = inf.readInt(n - 1, maxM, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        int z = inf.readInt(1, 100000, "z");
        inf.readEoln();

        ensuref(x != y, "Edge %d: x (%d) and y (%d) must be different", i + 1, x, y);

        int a = min(x, y), b = max(x, y);
        ensuref(!edges.count({a, b}), "Multiple edges between cities %d and %d (edge index %d)", a, b, i + 1);
        edges.insert({a, b});

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<bool> vis(n + 1, false);
    vector<int> stack;
    stack.push_back(1);
    vis[1] = true;
    int seen = 1;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                ++seen;
                stack.push_back(v);
            }
        }
    }
    ensuref(seen == n, "The input graph is not connected: only %d out of %d nodes are reachable from node 1", seen, n);

    inf.readEof();
}
