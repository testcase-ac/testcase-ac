#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(N - 1, 500, "M");
    inf.readSpace();
    int maxK = min(N - 2, 3);
    int K = inf.readInt(0, maxK, "K");
    inf.readEoln();

    // Read execution times
    vector<int> t = inf.readInts(N, 1, 1000000, "t_i");
    inf.readEoln();

    // Read edges and build graph
    vector<vector<int>> adj(N + 1);
    vector<int> indeg(N + 1, 0), outdeg(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "S_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "E_i");
        inf.readEoln();

        ensuref(u != v,
                "Self loop detected at edge %d: (%d -> %d)", i + 1, u, v);

        adj[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }

    // Check there is exactly one source (indegree 0) and it's node 1
    int cntSource = 0;
    for (int i = 1; i <= N; i++) {
        if (indeg[i] == 0) cntSource++;
    }
    ensuref(cntSource == 1,
            "There must be exactly one source, found %d", cntSource);
    ensuref(indeg[1] == 0,
            "Node 1 must be the unique starting node with indegree zero");

    // Check there is exactly one sink (outdegree 0)
    int cntSink = 0;
    for (int i = 1; i <= N; i++) {
        if (outdeg[i] == 0) cntSink++;
    }
    ensuref(cntSink == 1,
            "There must be exactly one sink, found %d", cntSink);

    // Check reachability from node 1
    vector<char> vis(N + 1, false);
    queue<int> q;
    vis[1] = true;
    q.push(1);
    int seen = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                seen++;
            }
        }
    }
    ensuref(seen == N,
            "Graph is not fully reachable from node 1: reached %d of %d", seen, N);

    // Check acyclicity via Kahn's algorithm
    vector<int> indeg2 = indeg;
    queue<int> q2;
    for (int i = 1; i <= N; i++) {
        if (indeg2[i] == 0) q2.push(i);
    }
    int topoCount = 0;
    while (!q2.empty()) {
        int u = q2.front(); q2.pop();
        topoCount++;
        for (int v : adj[u]) {
            indeg2[v]--;
            if (indeg2[v] == 0) {
                q2.push(v);
            }
        }
    }
    ensuref(topoCount == N, "Graph contains a cycle");

    inf.readEof();
    return 0;
}
