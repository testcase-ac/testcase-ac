#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Prepare to detect multiple edges and self-loops
    vector< unordered_set<int> > seen(N+1);
    vector<pair<int,int>> edges;
    edges.reserve(M);

    // Read edges
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d -> %d)", i, u, v);
        auto &st = seen[u];
        auto res = st.insert(v);
        ensuref(res.second, "Multiple edges detected: (%d -> %d)", u, v);

        edges.emplace_back(u, v);
    }

    // Build adjacency and compute indegrees
    vector<vector<int>> adj(N+1);
    vector<int> indeg(N+1, 0);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        indeg[v]++;
    }

    // Check for cycles via Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    int visited = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited++;
        for (int v : adj[u]) {
            if (--indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    ensuref(visited == N, "The graph must be acyclic (DAG), but a cycle was found");

    // Read A, B, K
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readSpace();
    int K = inf.readInt(0, N-2, "K");
    inf.readEoln();
    ensuref(A != B, "A and B must be different: A=%d, B=%d", A, B);

    // Read intermediate nodes C_i
    vector<bool> used(N+1, false);
    for (int i = 0; i < K; i++) {
        int c = inf.readInt(1, N, "C_i");
        inf.readEoln();
        ensuref(c != A && c != B,
                "Intermediate node C_%d must differ from A and B: C=%d, A=%d, B=%d",
                i, c, A, B);
        ensuref(!used[c],
                "Intermediate node C_%d = %d is repeated", i, c);
        used[c] = true;
    }

    inf.readEof();
    return 0;
}
