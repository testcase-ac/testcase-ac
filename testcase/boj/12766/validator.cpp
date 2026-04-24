#include "testlib.h"
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate primary parameters
    int n = inf.readInt(2, 5000, "n");
    inf.readSpace();
    int b = inf.readInt(1, n-1, "b");
    inf.readSpace();
    int s = inf.readInt(1, b, "s");
    inf.readSpace();
    int r = inf.readInt(1, 50000, "r");
    inf.readEoln();

    // Prepare adjacency lists and edge-set for duplicate detection
    vector<vector<int>> adj(n+1), radj(n+1);
    unordered_set<long long> seen;
    seen.reserve(r * 2);

    // Read roads
    for (int i = 0; i < r; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int l = inf.readInt(0, 10000, "l");
        inf.readEoln();

        long long key = ( (long long)u << 32 ) | (unsigned long long)v;
        ensuref(seen.find(key) == seen.end(),
                "Multiple edges detected between %d and %d", u, v);
        seen.insert(key);

        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    // Check strong connectivity via BFS from node 1 and on reversed graph
    vector<char> vis(n+1, 0);
    queue<int> q;

    // Forward BFS from node 1
    vis[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ensuref(vis[i], "Node %d is not reachable from node 1", i);
    }

    // Reverse BFS from node 1 (to check all can reach 1)
    fill(vis.begin(), vis.end(), 0);
    vis[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : radj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ensuref(vis[i], "Node %d cannot reach node 1", i);
    }

    inf.readEof();
    return 0;
}
