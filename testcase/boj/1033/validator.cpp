#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <numeric>
using namespace std;

int gcd(int a, int b) {
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // 2. Read N-1 edges
    vector<tuple<int,int,int,int>> edges;
    set<pair<int,int>> edge_set;
    vector<vector<pair<int,int>>> adj(N); // for connectivity check

    for (int i = 0; i < N-1; ++i) {
        int a = inf.readInt(0, N-1, "a");
        inf.readSpace();
        int b = inf.readInt(0, N-1, "b");
        inf.readSpace();
        int p = inf.readInt(1, 9, "p");
        inf.readSpace();
        int q = inf.readInt(1, 9, "q");
        inf.readEoln();

        ensuref(a != b, "Edge %d: a == b (%d == %d), self-loops are not allowed", i+1, a, b);

        // No multiple edges in either direction
        ensuref(!edge_set.count({a, b}), "Multiple edge between %d and %d detected (direction a->b)", a, b);
        ensuref(!edge_set.count({b, a}), "Multiple edge between %d and %d detected (direction b->a)", a, b);
        edge_set.insert({a, b});
        edge_set.insert({b, a});

        edges.emplace_back(a, b, p, q);

        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }

    // 3. Check that the graph is connected (since N-1 edges, must be a tree)
    vector<bool> vis(N, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& pr : adj[u]) {
            int v = pr.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                cnt++;
            }
        }
    }
    ensuref(cnt == N, "The graph is not connected: only %d/%d nodes reachable from node 0", cnt, N);

    inf.readEof();
}
