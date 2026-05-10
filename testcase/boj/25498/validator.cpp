#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // 2. Read string of length N, lowercase only
    string s = inf.readToken("[a-z]{1,500000}", "label_string");
    ensuref(int(s.size()) == N, "The label string length (%d) does not match N (%d)", int(s.size()), N);
    inf.readEoln();

    // 3. Read N-1 edges
    vector<vector<int>> adj(N+1); // 1-based
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected at edge %d: (%d, %d)", i+1, u, v);
        edges.insert({a, b});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 4. Check that the graph is a tree (connected and acyclic)
    // Since N-1 edges and N nodes, only need to check connectivity

    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!vis[nxt]) {
                vis[nxt] = true;
                q.push(nxt);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "The graph is not connected: only %d nodes reachable from node 1 (N=%d)", cnt, N);

    inf.readEof();
}
